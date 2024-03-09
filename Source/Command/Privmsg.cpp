#include "Privmsg.hpp"

Privmsg::Privmsg() { }
Privmsg::Privmsg(const Privmsg& rhs) {(void) rhs;}
Privmsg& Privmsg::operator=(const Privmsg& rhs) {(void)rhs;return *this;}
Privmsg::~Privmsg() { }

void	Privmsg::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	size_t					index;

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

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 2) {
		reply.errNoRecipient(client, "PRIVMSG");
		return;
	}
	splitByComma(target, message.getParam()[1]);
	for (size_t i = 0; i < target.size(); i++) {
		if (target[i][0] == '#' || target[i][0] == '&') {
			Channel* channel = resource.findChannel(target[i]);
			if (channel == NULL) {
				reply.errNoSuchNick(client, target[i]);
				return;
			} else if (!channel->hasClient(client)) {
				reply.errCannotSendToChan(client, channel);
				return;
			}
		} else {
			if (resource.findClient(target[i]) == NULL) {
				reply.errNoSuchNick(client, target[i]);
				return;
			}
		}
	}
	if (message.getParam().size() < 3) {
		reply.errNoTextToSend(client);
		return;
	}
	// :<nickname> PRIVMSG <target> <comment>
	for (size_t i = 0; i < target.size(); i++) {
		if (target[i][0] == '#' || target[i][0] == '&') {
			const std::set<Client*>& clientList = resource.findChannel(target[i])->getClientList();
			std::set<Client*>::iterator it;
			for (it = clientList.begin(); it != clientList.end(); it++) {
				if ((*it)->getClientFd() != client->getClientFd())
					SendMessageToClient(client, target[i], message.getParam()[2]);
			}
		}
		else {
			SendMessageToClient(client, target[i], message.getParam()[2]);
		}
	}
}

void	Privmsg::SendMessageToClient(Client* client, const std::string &target, const std::string comment) {
	std::string message;
	
	message = ":" + client->getNickname() + " PRIVMSG ";
	message += target + " :" + comment + "\r\n";
	client->addWriteBuffer(message);
}
