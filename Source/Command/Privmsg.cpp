#include "Privmsg.hpp"

Privmsg::Privmsg() { }
Privmsg::Privmsg(const Privmsg& rhs) { }
Privmsg& Privmsg::operator=(const Privmsg& rhs) { }
Privmsg::~Privmsg() { }

void	Privmsg::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	int					index;

	while ((index = param.find(',')) != std::string::npos) {
		tmp = param.substr(0, index);
		target.push_back(tmp);
		param.erase(0, index + 2);
	}
	if (param.size()) target.push_back(param);
}

void	Privmsg::execute(Resource& resource, Message message) {
	std::vector<std::string> target;
	Client* client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		// ERR_NORECIPIENT
		return;
	}
	splitByComma(target, message.getParam()[1]);
	for (size_t i = 0; i < target.size(); i++) {
		if (target[i][0] == '#' || target[i][0] == '&') {
			if (resource.findClient(target[i]) == NULL) {
				// ERR_NOSUCHNICK
				return;
			}
		} else {
			Channel* channel = resource.findChannel(target[i]);
			if (channel == NULL) {
				// ERR_NOSUCHNICK(CHANNEL)
				return;
			} else if (!channel->hasClient(client)) {
				// ERR_CANNOTSENDTOCHAN
				return;
			}
		}
	}
	if (message.getParam().size() < 3) {
		// ERR_NOTEXTTOSEND
		return;
	}
	for (size_t i = 0; i < target.size(); i++) {
		if (target[i][0] == '#' || target[i][0] == '&')
			resource.findClient(target[i])->addWriteBuffer(message.getParam()[2] + "\r\n");
		else {
			const std::set<Client*>& clientList = resource.findChannel(target[i])->getClientList();
			std::set<Client*>::iterator it;
			for (it = clientList.begin(); it != clientList.end(); it++)
				(*it)->addWriteBuffer(message.getParam()[2] + "\r\n");
		}
	}
	// :<nickname> PRIVMSG <target> <comment>
}