#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "Irc.hpp"

class Client {
	public:
		Client(int client_fd);
		Client(const Client& rhs);
		Client& operator=(const Client& rhs);
		~Client();

		void addReadbuf(std::string str);
		std::string& getReadbuf();

		bool&	getRegistered();
		bool&	getInfocomplete();
		bool&	getPasswdclear();

		void	setNickname(std::string msg);
		void	setUsername(std::string msg);
		void	checkRegistered();
		void	addWriteBuf(std::string rhs);
		std::string	getWriteBuf();

	private:
		Client();

		int _client_fd;
		int _info_cnt;

		std::string	_readbuf;
		std::string	_sendbuf;
		std::string	_nickname;
		std::string	_username;
		std::string	_realname;
		std::string	_old_nickname;

		bool	_registered;
		bool	_infocomplete;
		bool	_passwdclear;
		bool	_nickname_on;
		bool	_username_on;
};

#endif