#include "Server.hpp"

Server::Server() {}
Server::Server(const Server& rhs) {(void)rhs;}
Server& Server::operator=(const Server& rhs) {(void)rhs; return *this;}

Server::Server(const int& port, const std::string& password)
			: password(password), port(port)
			{std::cout << "Starting Server\n";}

Server::~Server() {std::cout << "Closing Server\n";}

void Server::initServerinfo() {
	resource.setPassword(password);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);
}

void Server::initServerSocket() {
	if ((serverFd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Socket failed\n";
		throw std::exception();
	}
	std::cout << "Server socket fd is " << serverFd << '\n';

	fcntl(serverFd, F_SETFL, O_NONBLOCK);

	int optval = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
		std::cerr << "Setsockopt failed\n";
		throw std::exception();
	}
	if (bind(serverFd, reinterpret_cast<struct sockaddr*>(&servAddr), sizeof(servAddr)) < 0) {
		std::cerr << "Bind failed\n";
		throw std::exception();
	}
	if (listen(serverFd, 10) < 0) {
		std::cerr << "Listen failed\n";
		throw std::exception();
	}
	if ((kqFd = kqueue()) < 0) {
		std::cerr << "Kqueue failed\n";
		throw std::exception();
	}
	return ;
}

void Server::networkProcess() {
	registerSocketToKqueue(serverFd);
	std::cout << "Server listening on port: " << port << '\n';
	while (true) {
		int eventCnt = kevent(kqFd, NULL, 0, eventList, MAX_EVENTS, NULL);
		if (eventCnt == -1) {
			std::cerr << "Kevent wait failed\n";
			throw std::exception();
		}
		for (int i = 0; i < eventCnt; ++i) {
			int tmpFd = eventList[i].ident;
			if (eventList[i].filter == EVFILT_READ) {
				if (tmpFd == serverFd) {
					acceptNewClient();
				} else {
					recieveMessageFromClient(tmpFd);
				}
			} else if (tmpFd != serverFd && eventList[i].filter == EVFILT_WRITE) {
				sendMessageToClient(tmpFd);
			}
		}
	}
}

void Server::recieveMessageFromClient(const int& fd) {
	Client* client = resource.findClient(fd);

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	ssize_t bytesRecieved = recv(fd, buffer, sizeof(buffer), 0);
	if (bytesRecieved <= 0) {
		if (bytesRecieved == 0 || errno != EAGAIN)
			std::cerr << "disconnected\n";
		else
			std::cerr << "Recv failed\n";
		disconnectClient(fd);
	} else {
		client->addReadBuffer(buffer);
		if (client->hasCompleteMessage()) {
			std::vector<Message> messages;
			messageHandler.handleMessage(messages, fd, client->getReadBuffer());
			for (size_t i = 0; i < messages.size(); i++) {
				Command* command = resource.findCommand(messages[i].getFirstParam());
				std::cout << messages[i].getOriginalMessage() << '\n';
				if (command != NULL)
					command->execute(resource, messages[i]);
			}
			client->deleteReadBuffer();
		}
	}
}

void Server::sendMessageToClient(const int& fd) {
	Client* client = resource.findClient(fd);
	std::string tmp;

	size_t index = client->getWriteBuffer().find("\r\n");
	if (index != std::string::npos) {
		tmp = client->getWriteBuffer().substr(0, index + 2);
		client->deleteWriteBuffer();
		send(fd, tmp.c_str(), tmp.size(), 0);
	}
}

void Server::disconnectClient(const int& fd) {
	close(fd);
	EV_SET(&changeList[0], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	EV_SET(&changeList[1], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	kevent(kqFd, changeList, 2, NULL, 0, NULL);
	resource.removeClientFromChannel(resource.findClient(fd));
	resource.removeClient(fd);
}

void Server::acceptNewClient() {
	struct sockaddr_in clntAddr;
	int newSocket;

	socklen_t addr_len = sizeof(clntAddr);
	newSocket = accept(serverFd, reinterpret_cast<struct sockaddr*>(&clntAddr), &addr_len);
	if (newSocket < 0) {
		std::cerr << "Accept failed\n";
		throw std::exception();
	}
	if (resource.getClientCount() < MAX_CLIENT) {
		Client	newClient(newSocket);

		fcntl(newSocket, F_SETFL, O_NONBLOCK);
		registerSocketToKqueue(newSocket);
		resource.addClient(newSocket);
		std::cout << "New connection accepted from " << inet_ntoa(clntAddr.sin_addr) << '\n';
	} else {
		std::cerr << "Aleady too many clients is exist!!" << std::endl;
	}
}

void Server::registerSocketToKqueue(const int& socketFd) {
	EV_SET(&changeList[0], socketFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	EV_SET(&changeList[1], socketFd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	if (kevent(kqFd, changeList, 2, NULL, 0, NULL) == -1) {
		std::cerr << "Register socket to kqueue failed\n";
		throw std::exception();
	}
}
