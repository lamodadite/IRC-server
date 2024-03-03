#ifndef SERVER_HPP
#define SERVER_HPP

# include "Irc.hpp"
# include "Client.hpp"

# define MAX_EVENTS 16
# define MAX_CLIENT 20

class Server {
	public:
		Server(std::string port, std::string passwd);
		~Server();
		
		void	setServerinfo(char *port);
		void	setServerSocket();
		void	networkProcess();
		void	acceptNewClient();
		void	disconnectClient(int fd);
		void	recvMsgFromClient(int fd);
		void	parseReadbuf(int fd, Client* client); 
		void	fillClientInfo(Client* client, std::string msg);

		Client* getClient(int fd);

	private:
		Server();
		Server(const Server& rhs);
		Server& operator=(const Server& rhs);

		int	_server_fd;
		int _kq_fd;
		int _event_cnt;

		// read write 둘 다 설정하기 위해서 2짜리 배열
		struct kevent	_change_list[2];
		struct kevent	_event_list[MAX_EVENTS];

		struct addrinfo	*_serv_adr;
		struct addrinfo	_hints;

		std::string _port;
		std::string _passwd;

		std::map<std::string, Channel>	_ct_channel;
		std::map<int, Client> 					_ct_client;
};

#endif