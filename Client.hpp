#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "Irc.hpp"

class Client {
	public:
		Client(const int& clientFd);
		Client(const Client& rhs);
		~Client();

		const std::string& getNickname() const;
		bool	getRegistered();
		bool	getInfocomplete();
		bool	getPasswordclear();
		const std::string&	getReadBuffer() const;
		const std::string&	getWriteBuffer() const;

		void	checkInfoCompleted();

		void	setNickname(const std::string& nickname);
		void	setUsername(const std::string& username);
		void	addReadBuffer(const std::string& str);
		void	addWriteBuffer(const std::string& str);

		void	deleteReadBuffer();
		void	deleteWriteBuffer();

		bool	hasCompleteMessage();

	private:
		Client();
		Client& operator=(const Client& rhs);

		int clientFd;
		int infoCnt;

		std::string	readBuffer;
		std::string	sendBuffer;
		std::string	nickname;
		std::string	username;
		std::string	realname;
		std::string	oldNickname;

		bool	registered;
		bool	infoComplete;
		bool	passwordClear;
		bool	nicknameOn;
		bool	usernameOn;
};

#endif