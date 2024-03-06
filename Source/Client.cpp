#include "Client.hpp"

Client::Client() {};

Client::Client(const Client& rhs)
			: clientFd(rhs.clientFd), infoCnt(rhs.infoCnt), 
			readBuffer(rhs.readBuffer), sendBuffer(rhs.sendBuffer), 
			nickname(nickname), username(username), realname(realname), 
			oldNickname(oldNickname), registered(rhs.registered), 
			passed(rhs.passed), nicknameOn(rhs.nicknameOn), usernameOn(rhs.usernameOn) {}

Client& Client::operator=(const Client& rhs) {(void)rhs; return *this;}

Client::Client(const int& clientFd)
			: clientFd(clientFd), infoCnt(0), readBuffer(""), 
			sendBuffer(""), nickname(""), username(""), realname(""), 
			oldNickname(""), registered(false),	passed(false),
			nicknameOn(false), usernameOn(false) {}

Client::~Client() {}

const std::string&	Client::getReadBuffer() const {return readBuffer;}

const std::string&	Client::getWriteBuffer() const {return sendBuffer;}

void	Client::addReadBuffer(const std::string& str) {readBuffer += str;}

void	Client::addWriteBuffer(const std::string& str) {sendBuffer += str;}

void	Client::setPassed(const bool& passed) {this->passed = passed;}

const bool&	Client::getPassed() const {return passed;}

const bool&	Client::getRegistered() const {return registered;}

const std::string&	Client::getNickname() const {return nickname;}

void	Client::setNickname(const std::string& nickname) {
	this->nickname = nickname;
	nicknameOn = true;
}

const std::string&	Client::getOldNickname() const {return oldNickname;}

void	Client::setOldNickname(const std::string& oldNickname) {this->oldNickname = oldNickname;}

void	Client::setUsername(const std::string& username) {
	this->username = username;
	usernameOn = true;
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

bool	Client::canBeRegistered() {
	if (nicknameOn && usernameOn && passed) {
		registered = true;
		return true;
	}
	return false;
}
