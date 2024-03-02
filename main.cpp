#include "Server.hpp"

int main(int ac, char *av[]) {
	if (ac != 3) {
		std::cerr << "The right usage is: ./ircserv [port] [passwd]\n";
		return 1;
	}
	try {
		Server server(av[1], av[2]);

		server.setServerinfo(av[1]);
		server.setServerSocket();
		server.networkProcess();
	} catch (std::exception& e) {
		return 1;
	}
	return 0;
}