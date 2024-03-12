#include "Kick.hpp"

Kick::Kick() {}
Kick::Kick(const Kick& rhs) {(void)rhs;}
Kick& Kick::operator=(const Kick& rhs) {(void)rhs; return *this;}
Kick::~Kick() {}

void	Kick::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	size_t					index;

	while ((index = param.find(',')) != std::string::npos) {
		tmp = param.substr(0, index);
		target.push_back(tmp);
		param.erase(0, index + 2);
	}
	if (param.size()) target.push_back(param);
}

void Kick::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());
	Channel* channel;
	Client* kickedClient;
	std::vector<std::string> target;

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 3) {
		reply.errNeedMoreParams(client, "KICK");
		return;
	}
	channel = resource.findChannel(message.getParam()[1]);
	if (channel == NULL) {
		reply.errNoSuchChannel(client, message.getParam()[1]);
		return;
	} else if (!channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	} 	
	splitByComma(target, message.getParam()[2]);
	for (size_t i = 0; i < target.size(); i++)
	{
		kickedClient = resource.findClient(target[i]);
		if (kickedClient == NULL || !channel->hasClient(kickedClient)) {
			reply.errUserNotInChannel(client, target[i], channel);
			continue;
		} else if (!channel->hasClient(client)) {
			reply.errNotOnChannel(client, channel);
			continue;
		}
		// :<nickname> KICK <channel> <kicked nickname>
		if (message.getParam().size() == 3 || message.getParam()[3] == "")
			sendMessageToChannel(client, channel, kickedClient, kickedClient->getNickname());
		else
			sendMessageToChannel(client, channel, kickedClient, message.getParam()[3]);
		channel->removeClient(kickedClient);
		channel->removeOperator(kickedClient);
	}
}

void	Kick::sendMessageToChannel(Client *client, Channel* channel, Client *kickedClient, const std::string& reason) {
	const std::set<Client*>& clientList = channel->getClientList();
	std::string message;

	message = ":" + client->getNickname() + " KICK ";
	message += channel->getName() + " " + kickedClient->getNickname() + " :" + reason + "\r\n";

	std::set<Client*>::iterator iter;
	for (iter = clientList.begin(); iter != clientList.end(); iter++) {
		(*iter)->addWriteBuffer(message);
	}
}