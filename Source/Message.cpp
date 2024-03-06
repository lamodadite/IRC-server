#include "Message.hpp"

Message::Message(): isCommand(false), clientFd(0) {}
Message::Message(const Message& rhs) : isCommand(rhs.isCommand), clientFd(rhs.clientFd), param(rhs.param), firstParam(rhs.firstParam), originalMessage(rhs.originalMessage) {}
Message& Message::operator=(const Message& rhs) {
	if (this == &rhs)
		return *this;
	isCommand = rhs.isCommand;
	clientFd = rhs.clientFd;
	firstParam = rhs.firstParam;
	param = rhs.param;
	originalMessage = rhs.originalMessage;
	return *this;
}
Message::~Message() {}

const std::string& Message::getFirstParam() const {return firstParam;}

const std::vector<std::string>& Message::getParam() const {return param;}

const int& Message::getClientFd() const {return clientFd;}

const bool& Message::getIsCommand() const {return isCommand;}
 
const std::string& Message::getOriginalMessage() const {return originalMessage;}

void	Message::setClientFd(const int& clientFd) {this->clientFd = clientFd;}

void	Message::setIsCommand(const bool& isCommand) {this->isCommand = isCommand;}

void	Message::setParam(const std::vector<std::string>& param) {this->param = param;}

void	Message::setFirstParam(const std::string& param) {this->firstParam = param;}

void	Message::setOriginalMessage(const std::string& message) {this->originalMessage = message;}