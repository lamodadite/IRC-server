#include "MessageHandler.hpp"

MessageHandler::MessageHandler() { }
MessageHandler::MessageHandler(const MessageHandler& rhs) { }
MessageHandler& MessageHandler::operator=(const MessageHandler& rhs) { }
MessageHandler::~MessageHandler() { }

void MessageHandler::handleMessage(std::vector<Message>& messages, const int& fd, std::string buffer) {
	std::vector<std::string>	splitedBuffer;

	splitBuffer(splitedBuffer, buffer);
	for (size_t i = 0; i < splitedBuffer.size(); i++) {
		if (!splitedBuffer[i].size()) continue;
		Message	message;
		splitToParam(splitedBuffer[i], message);
		message.setClientFd(fd);
		messages.push_back(message);
	}
}

void	MessageHandler::splitBuffer(std::vector<std::string>& splitedBuffer, std::string& buffer) {
	std::string	tmp;
	int					index;

	while ((index = buffer.find("\r\n")) != std::string::npos) {
		tmp = buffer.substr(0, index);
		splitedBuffer.push_back(tmp);
		buffer.erase(0, index + 2);
	}
}

void	MessageHandler::splitToParam(std::string& splitedBuffer, Message& message) {
	std::string	tmp;
	std::vector<std::string>	params;
	int					index;
	int					colonIndex;

	message.setOriginalMessage(splitedBuffer);
	while (true) {
		index = splitedBuffer.find(' ');
		colonIndex = splitedBuffer.find(':');
		if (colonIndex != std::string::npos && colonIndex < index) {
			tmp = splitedBuffer.substr(0, colonIndex);
			params.push_back(tmp);
			splitedBuffer.erase(0, colonIndex);
			break ;
		} else if (index == std::string::npos) {
			break ;
		}
		tmp = splitedBuffer.substr(0, index);
		params.push_back(tmp);
		splitedBuffer.erase(0, index + 1);
	}
	if (splitedBuffer.size()) params.push_back(splitedBuffer);
	message.setParam(params);
	message.setFirstParam(params[0]);
	if (isCommand(params[0])) message.setIsCommand(true);
}

bool	MessageHandler::isCommand(const std::string& param) {
	const std::vector<std::string> commands = {
			"NICK",
			"INVITE",
			"JOIN",
			"KICK",
			"MODE",
			"PASS",
			"TOPIC",
			"USER",
			"PRIVMSG"
	};
	for (int i = 0; i < commands.size(); i++) {
		if (param == commands[i]) return true;
	}
	return false;
}


// 	for (size_t i = 0; i < msg.size(); i++) {
// 		if (!msg[i].size()) continue; // 빈문자열인 경우 패스 <<< 빈문자열을 보내는 경우에도 응답하는 일이있으면 따로 처리 해야할듯
// 		// 아직 정보들이 다들어오지 않은 client
// 		if (client->getRegistered() == false) {
// 			if (client->getInfocomplete() == false) fillClientInfo(client, msg[i]); //client 멤버함수로 만들려고 했으나 명령어 실행때문에.
// 			if (client->getInfocomplete() == true) {
// 				// client가 등록 되었다는 것을 알림. 알려야하는 내용들은 문서에서
// 				sendClientRegistered(fd, client);
// 				client->getRegistered() = true;
// 			} else {
// 				// 
// 			}
// 		} 
// 		else {
// 			checkCommand(client, msg[i]);
// 		}
// 	} 

// void Server::fillClientInfo(Client* client, std::string msg) {
// 	if (!strncmp("NICK", msg.c_str(), 4)) {
// 		msg.erase(0, 5);
// 		client->setNickname(msg);
// 	} else if (!strncmp("USER", msg.c_str(), 4)) {
// 		msg.erase(0, 5);
// 		client->setUsername(msg);
// 	} else if (!strncmp("PASS", msg.c_str(), 4)) {
// 		msg.erase(0, 5);
// 		if (msg == _passwd) {
// 			client->getPasswdclear() = 1;
// 		}
// 	}
// 	client->checkRegistered();
// }


