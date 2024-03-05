#ifndef SERVER_HPP
#define SERVER_HPP

# include "Irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Resource.hpp"
# include "MessageHandler.hpp"

class Server {
	public:
		Server(const int& port, const std::string& passwd);
		~Server();
		
		void	initServerinfo();
		void	initServerSocket();
		void	networkProcess();
		void	acceptNewClient();

	private:
		Server();
		Server(const Server& rhs);
		Server& operator=(const Server& rhs);

		void	disconnectClient(const int& fd);
		void	recieveMessageFromClient(const int& fd);
		void	sendMessageToClient(const int& fd);
		void	registerSocketToKqueue(const int& socketFd);

		static const int	MAX_EVENTS = 16;
		static const int	MAX_CLIENT = 20;

		struct kevent	eventList[MAX_EVENTS];
		struct kevent	changeList[2];
		struct sockaddr_in	servAddr;
		
		Resource resource;
		MessageHandler messageHandler;

		std::string	password;
		int	port;
		int	serverFd;
		int	kqFd;
};

#endif