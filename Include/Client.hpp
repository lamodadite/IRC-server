#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "Irc.hpp"

class Channel;

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
		const std::string&	getUsername() const;
		const std::string&	getIp() const;
		const std::string&	getWriteBuffer() const;
		const int& getClientFd() const;

		void	setPassed(const bool& passed);
		void	setNickname(const std::string& nickname);
		void	setOldNickname(const std::string& oldNickname);
		void	setUsername(const std::string& username);
		void	setIp(const std::string& ip);
		void	addReadBuffer(const std::string& str);
		void	addWriteBuffer(const std::string& str);
		void	addJoinedChannel(Channel* channel);
		void	addInvitedChannel(Channel* channel);

		void	deleteReadBuffer();
		void	deleteWriteBuffer();
		void	deleteJoinedChannel(Channel* channel);

		bool	hasCompleteMessage();
		bool	canBeRegistered();

	private:
		Client();
		Client& operator=(const Client& rhs);

		int clientFd;
		int infoCnt;

		std::set<Channel *>	joinedChannel;
		std::set<Channel *>	invitedChannel;
		std::string	readBuffer;
		std::string	sendBuffer;
		std::string	nickname;
		std::string	username;
		std::string	realname;
		std::string	oldNickname;
		std::string	ip;

		bool	registered;
		bool	passed;
		bool	nicknameOn;
		bool	usernameOn;
};

#endif