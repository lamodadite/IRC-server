#include "Server.hpp"

// 쓸일없어서 private
Server::Server();
Server::Server(const Server& rhs) {(void)rhs;}
Server& Server::operator=(const Server& rhs) {(void)rhs; return *this;}

Server::Server(std:: string port, std::string passwd) : _port(port), _passwd(passwd) {
	std::cout << "Starting Server\n";
	memset(_hints, 0, sizeof(_hints));
	// IPv4 주소 패밀리 사용
	this->_hints.ai_family = AF_INET;
	// TCP 스트림 소켓
	this->_hints.ai_socktype = SOCK_STREAM;
	// AI_PASSIVE 수신 대기 소켓을 생성
	this->_hints.ai_flags = AI_PASSIVE;
}

Server::~Server() {std::cout << "Closing Server\n";}

void Server::setServerinfo(char *port) {
	// 포트 변환하기 편함, 첫인자는 호스트명이나 ip주소 문자열. 우린 로컬이니 0.
	if (getaddrinfo(0, port, &_hints, &_serv_adr) < 0) {
		std::cerr << "Failed to set Server Addrinfo\n";
		throw std::exception();
	}
	return 0;
}

void setServerSocket() {
	if ((this->_server_fd = socket(_serv_adr->ai_family, _serv_adr->ai_socktype, _serv_adr->ai_protocol)) < 0) {
		std::cerr << "Socket failed\n";
		throw std::exception();
	}
	std::cout << "Server socket fd is " << _server_fd << '\n';

	// register port

	// Set socket to non-blocking, F_SETFL 파일 디스크립터 플래그 설정, O_NONBLOCK 비차단 모드로 설정.
	fcntl(_server_fd, F_SETFL, O_NONBLOCK);

	// SOL_SOCKET 소켓 옵션을 설정, SO_REUSEADDR 재사용 가능한 주소로 설정 TIME_WAIT으로 인한 점유상태 문제 해결.
	int optval = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
		std::cerr << "Setsockopt failed\n";
		throw std::exception();
	}

	// Bind socket to port
	if (bind(_server_fd, _serv_adr, sizeof(_serv_adr)) < 0) {
		std::cerr << "Bind failed\n";
		throw std::exception();
	}

	// Start listening
	if (listen(_server_fd, 10) < 0) {
		std::cerr << "Listen failed\n";
		throw std::exception();
	}

	// Create kqueue
	if ((_kq_fd = kqueue()) < 0) {
		std::cerr << "Kqueue failed\n";
		throw std::exception();
	}

	// getaddrinfo 함수로 동적 할당된 메모리를 해제해주는 작업.
	freeaddrinfo(_serv_adr);
	return ;
}

void Server::networkProcess() {
	// serverFd kqueue 이벤트에 추가
	registerSocketToKqueue(_server_fd);
	std::cout << "Server listening on port: " << _port << '\n';
	// loop 진입, ctrl + c 시그널 처리 할것인지??
	while (true) {
		// Wait for events
		// 이벤트가 발생한 수를 리턴. 실패하면 -1
		int _event_cnt = kevent(_kq_fd, NULL, 0, _event_list, MAX_EVENTS, NULL);
		if (_event_cnt == -1) {
			std::cerr << "Kevent wait failed\n";
			throw std::exception();
		}
		// Handle events
		for (int i = 0; i < _event_cnt; ++i) {
			int tmp_fd = _event_list[i].ident; // 발생한 이벤트의 fd
			if (_event_list[i].filter == EVFILT_READ) {
				if (tmp_fd == _server_fd) { // Server socket event (new connection)
					acceptNewClient();
				} else { // Client socket event (data available)
					recvMsgFromClient(tmp_fd);
				}
			} else if (_event_list[i].filter == EVFILT_WRITE) {
				// WRITE 이벤트의 경우
			}
		}
	}
}

void Server::recvMsgFromClient(int fd) {
	Client *client;

	client = getClient(fd);
	char buffer[1024] = {0};
	ssize_t bytesRecieved = recv(fd, buffer, sizeof(buffer), 0);
	if (bytesRecieved <= 0) {
		if (bytesRecieved == 0 || errno != EAGAIN) {
			std::cerr << "disconnected\n";
		} else {
			std::cerr << "Recv failed\n";
		}
		disconnectClnt(fd);
	} else {
		std::cout << "Received: " << buffer << '\n';
		// set을 = 이 아닌 += 으로  구상할것
		client->setReadbuf(buffer);
		// HTTP 프로토콜에서 \r\n 줄바꿈을 나타냄. npos는 못찾았을경우 나오는 반환값
		// 자료를 덜받았으면 readbuf에 쌓아두고 더 수신을 기다림.
		if (client->getReadbuf().find("\r\n") != std::string::npos) {
			//client 정보 채우기랑 명령어들 구분하는법 공부하고 적용하기 여기가 제일 중요!!
			parseReadbuf(fd, client);
			//사용한 버퍼 처리 레퍼런스로 반환해서 clear가능
			client->getReadbuf().clear();
		}
	}
}

void Server::sendMsgToClent(int fd, char buffer[], int bytesRecieved) {
	// Echo back to the client
	send(fd, buffer, bytesRecieved, 0);
}

void Server::disconnectClnt(int fd) {
	close(fd);
	EV_SET(_change_list[0], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	EV_SET(_change_list[1], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	kevent(_kq_fd, _change_list, 2, NULL, 0, NULL);
}

void Server::acceptNewClient() {
	struct sockaddr_in clntAddr;
	int newSocket;

	socklen_t addr_len = sizeof(clntAddr);
	newSocket = accept(_server_fd, (struct sockaddr *)&clntAddr, &addr_len);
	if (newSocket < 0) {
		std::cerr << "Accept failed\n";
		throw std::exception();
	}
	// 일단은 연결을 하고 나중에 정보 기입을 요구
	if (_ct_client.size() < MAX_CLIENT) {
		Client	new_client(newSocket);

		// Set new socket to non-blocking
		fcntl(newSocket, F_SETFL, O_NONBLOCK);
		registerSocketToKqueue(newSocket);
		_ct_client.insert(std::pair<int, Client>(newSocket, new_client));
		std::cout << "New connection accepted from " << inet_ntoa(clntAddr.sin_addr) << '\n';
	} else {
		tooManyClient(newSocket);
	} 
}

void Server::registerSocketToKqueue(int socketFd) {
	// Register server socket to kqueue for read events
	// read write 둘다 설정해주기
	EV_SET(&_change_list[0], socketFd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	EV_SET(&_change_list[1], socketFd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
	// change_envent에 이벤트 큐에 대한 변경사항을 제출, 2개라서 세번째 인자 2입력.
	if (kevent(_kq_fd, _change_list, 2, NULL, 0, NULL) == -1) {
		std::cerr << "Register socket to kqueue failed\n";
		throw std::exception();
	}
}

Client* Server::getClient(int fd) {return &(_ct_client.at(fd));}