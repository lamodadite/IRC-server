#include "MessageHandler.hpp"

MessageHandler::MessageHandler() { }
MessageHandler::MessageHandler(const MessageHandler& rhs) { }
MessageHandler& MessageHandler::operator=(const MessageHandler& rhs) { }
MessageHandler::~MessageHandler() { }

std::vector<Message> MessageHandler::handleMessage(const int& fd, std::string buffer) {

}

// void Server::parseReadbuf(int fd, Client* client) {
// 	std::vector<std::string>	msg;
	
// 	splitReadbuf(msg, client); \r\n; ' ';
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
// }

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

// void Server::splitReadbuf(std::vector<std::string>& msg, Client* client) {
// 	std::string 	tmp;
// 	std::string&	readbuf = client->getReadbuf();
// 	int						idx;

// 	//명령어가 \r\n 으로 한번에 여러개가 올수 있다해서
// 	// 앞에서 완성된 메세지만 오게 해서 readbuf는 비워지고 \r\n이 연속으로 오는 경우 빈 문자열이 들어갈수도 있음.
// 	while ((idx = readbuf.find("\r\n")) != std::string::npos) {
// 		tmp = readbuf.substr(0, idx);
// 		msg.push_back(tmp);
// 		readbuf.erase(0, idx + 2);
// 	}
// }

