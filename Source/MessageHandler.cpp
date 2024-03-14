#include "MessageHandler.hpp"

MessageHandler::MessageHandler() {}
MessageHandler::MessageHandler(const MessageHandler& rhs) {(void)rhs;}
MessageHandler& MessageHandler::operator=(const MessageHandler& rhs) {(void)rhs; return *this;}
MessageHandler::~MessageHandler() {}

void MessageHandler::handleMessage(std::vector<Message>& messages, const int& fd, std::string buffer) {
	std::vector<std::string>	splitedBuffer;

	splitBuffer(splitedBuffer, buffer);
	for (std::size_t i = 0; i < splitedBuffer.size(); i++) {
		if (!splitedBuffer[i].size()) continue;
		Message	message;
		splitToParam(splitedBuffer[i], message);
		message.setClientFd(fd);
		messages.push_back(message);
	}
}

void	MessageHandler::splitBuffer(std::vector<std::string>& splitedBuffer, std::string& buffer) {
	std::string	tmp;
	std::size_t	index;

	while ((index = buffer.find("\r\n")) != std::string::npos) {
		tmp = buffer.substr(0, index);
		splitedBuffer.push_back(tmp);
		buffer.erase(0, index + 2);
	}
}

void	MessageHandler::splitToParam(std::string& splitedBuffer, Message& message) {
	std::string					tmp;
	std::vector<std::string>	params;
	std::size_t					index;
	std::size_t					colonIndex;

	message.setOriginalMessage(splitedBuffer);
	while (true) {
		index = splitedBuffer.find(' ');
		colonIndex = splitedBuffer.find(':');
		if (colonIndex != std::string::npos && (colonIndex < index || index == std::string::npos) ) {
			tmp = splitedBuffer.substr(0, colonIndex);
			if (tmp.size()) params.push_back(tmp);
			splitedBuffer.erase(0, colonIndex);
			break ;
		} else if (index == std::string::npos) {
			break ;
		}
		tmp = splitedBuffer.substr(0, index);
		if (tmp.size()) params.push_back(tmp);
		splitedBuffer.erase(0, index + 1);
	}
	if (splitedBuffer.size()) {
		if (splitedBuffer[0] == ':') splitedBuffer.erase(0, 1);
		params.push_back(splitedBuffer);
	}
	message.setParam(params);
	message.setFirstParam(params[0]);
	if (isCommand(params[0])) message.setIsCommand(true);
}

bool	MessageHandler::isCommand(const std::string& param) {
	const std::string commands[10] = {
			"NICK",
			"INVITE",
			"JOIN",
			"KICK",
			"MODE",
			"PASS",
			"TOPIC",
			"USER",
			"PRIVMSG"
			"PING",
	};
	for (int i = 0; i < 10; i++) {
		if (param == commands[i]) return true;
	}
	return false;
}
