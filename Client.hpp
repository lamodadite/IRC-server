#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "Irc.hpp"

class Client {
	public:
		Client(int client_fd);
		~CLient();

		void addReadbuf(std::string str);
		std::string& getReadbuf() const;

		bool&	getRegistered();
		bool&	getInfocomplete();
		bool&	getPasswdclear();


	private:
		Client();
		Client(const Client& rhs);
		Client& operator=(const Client& rhs);

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
};

#endif