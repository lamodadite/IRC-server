#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "Irc.hpp"

class Client {
	public:
		Client(const int& clientFd);
		Client(const Client& rhs);
		~Client();

		const std::string& getNickname() const;
		const std::string& getOldNickname() const;
		const bool&	getRegistered() const;
		const bool&	getPassed() const;
		const std::string&	getReadBuffer() const;
		const std::string&	getWriteBuffer() const;

		void	setPassed(const bool& passed);
		void	setNickname(const std::string& nickname);
		void	setOldNickname(const std::string& oldNickname);
		void	setUsername(const std::string& username);
		void	addReadBuffer(const std::string& str);
		void	addWriteBuffer(const std::string& str);

		void	deleteReadBuffer();
		void	deleteWriteBuffer();

		bool	hasCompleteMessage();
		bool	canBeRegistered();

	private:
		Client();
		Client& operator=(const Client& rhs);

		int clientFd;
		int infoCnt;

		std::set<Channel *>	joinedChannel;
		std::string	readBuffer;
		std::string	sendBuffer;
		std::string	nickname;
		std::string	username;
		std::string	realname;
		std::string	oldNickname;

		bool	registered;
		bool	passed;
		bool	nicknameOn;
		bool	usernameOn;
};

#endif