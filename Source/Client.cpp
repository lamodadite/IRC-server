#include "Client.hpp"
#include "Channel.hpp"

Client::Client() {};

Client::Client(const Client& rhs)
			: clientFd(rhs.clientFd), infoCnt(rhs.infoCnt), 
			readBuffer(rhs.readBuffer), sendBuffer(rhs.sendBuffer), 
			nickname(rhs.nickname), username(rhs.username), realname(rhs.realname), 
			oldNickname(rhs.oldNickname), registered(rhs.registered), 
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

void	Client::addJoinedChannel(Channel* channel) {joinedChannel.insert(channel);}

void	Client::addInvitedChannel(Channel* channel) {invitedChannel.insert(channel);}

const bool&	Client::getPassed() const {return passed;}
const bool&	Client::getRegistered() const {return registered;}
const std::string&	Client::getNickname() const {return nickname;}
const std::string&	Client::getOldNickname() const {return oldNickname;}
const std::string&	Client::getUsername() const {return username;}
const std::string&	Client::getIp() const {return ip;}
const int& Client::getClientFd() const {return clientFd;}

void	Client::setPassed(const bool& passed) {this->passed = passed;}

void	Client::setNickname(const std::string& nickname) {
	this->nickname = nickname;
	nicknameOn = true;
}

void	Client::setOldNickname(const std::string& oldNickname) {this->oldNickname = oldNickname;}

void	Client::setUsername(const std::string& username) {
	this->username = username;
	usernameOn = true;
}

void	Client::setIp(const std::string& ip) {
	this->ip = ip;
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
	if ((pos = sendBuffer.find("\r\n")) != std::string::npos)
		sendBuffer.erase(0, pos + 2);
}

void	Client::deleteJoinedChannel(Channel* channel) {
	std::set<Channel*>::iterator it = joinedChannel.find(channel);
	if (it != joinedChannel.end())
		joinedChannel.erase(it);
}

bool	Client::canBeRegistered() {
	if (nicknameOn && usernameOn && passed) {
		registered = true;
		return true;
	}
	return false;
}

