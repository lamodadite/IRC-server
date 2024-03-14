#include "Server.hpp"

static int	convertToPort(std::string port) {
	for (size_t i = 0; i < port.size(); i++)
		if (!std::isdigit(port[i])) return -1;
	long tmp = std::strtol(port.c_str(), NULL, 10);
	if (errno == ERANGE || tmp < 0 || tmp > 65535) return -1;
	return static_cast<int>(tmp);
}

int main(int ac, char *av[]) {
	if (ac != 3) {
		std::cerr << "The right usage is : ./ircserv <port> <password>\n";
		return 1;	
	}
	int port = convertToPort(av[1]);
	if (port == -1) {
		std::cerr << "Invalid port number : " << av[1] << "\n";
		return 1;
	}
	std::srand(std::time(NULL));
	try {
		Server server(port, av[2]);

		server.initServerinfo();
		server.initServerSocket();
		server.networkProcess();
	} catch (const std::exception& e) {
		return 1;
	}
	return 0;
}