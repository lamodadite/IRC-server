#include "Client.hpp"

Client::Client() {};

Client::Client(const Client& rhs)
			: clientFd(rhs.clientFd), infoCnt(rhs.infoCnt), 
			readBuffer(rhs.readBuffer), sendBuffer(rhs.sendBuffer), 
			nickname(nickname), username(username), realname(realname), 
			oldNickname(oldNickname), registered(rhs.registered), 
			infoComplete(rhs.infoComplete), passwordClear(rhs.passwordClear), 
			nicknameOn(rhs.nicknameOn), usernameOn(rhs.usernameOn) {}

Client& Client::operator=(const Client& rhs) {(void)rhs; return *this;}

Client::Client(const int& clientFd)
			: clientFd(clientFd), infoCnt(0), readBuffer(""), 
			sendBuffer(""), nickname(""), username(""), realname(""), 
			oldNickname(""), registered(false), infoComplete(false), 
			passwordClear(false), nicknameOn(false), usernameOn(false) {}

Client::~Client() {}

const std::string&	Client::getReadBuffer() const {return readBuffer;}

const std::string&	Client::getWriteBuffer() const {return sendBuffer;}

void	Client::addReadBuffer(const std::string& str) {readBuffer += str;}

void	Client::addWriteBuffer(const std::string& str) {sendBuffer += str;}

bool	Client::getInfocomplete() {return infoComplete;}

bool	Client::getPasswordclear() {return passwordClear;}

bool	Client::getRegistered() {return registered;}

const std::string&	Client::getNickname() const {return nickname;}

void	Client::setNickname(const std::string& nickname) {
	this->nickname = nickname;
	nicknameOn = true;
}

void	Client::setUsername(const std::string& username) {
	this->username = username;
	usernameOn = true;
}

void	Client::checkInfoCompleted() {
	if (nicknameOn && usernameOn && passwordClear)
		infoComplete = true;
}

bool	Client::hasCompleteMessage() {
	if (readBuffer.find("\r\n") != std::string::npos) return true;
	return false;
}

void	Client::deleteReadBuffer() {
	size_t pos;
	while ((pos = readBuffer.find("\r\n")) != std::string::npos)
		readBuffer.erase(0, pos + 2);
}

void	Client::deleteWriteBuffer() {
	size_t pos;
	while ((pos = sendBuffer.find("\r\n")) != std::string::npos)
		sendBuffer.erase(0, pos + 2);
}
