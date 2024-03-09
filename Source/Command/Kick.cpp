#include "Kick.hpp"

Kick::Kick() {}
Kick::Kick(const Kick& rhs) {(void)rhs;}
Kick& Kick::operator=(const Kick& rhs) {(void)rhs; return *this;}
Kick::~Kick() {}

void Kick::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());
	Channel* channel;
	Client* kickedClient;

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 3) {
		reply.errNeedMoreParams(client, "KICK");
		return;
	}
	channel = resource.findChannel(message.getParam()[1]);
	kickedClient = resource.findClient(message.getParam()[2]);

	if (channel == NULL) {
		reply.errNoSuchChannel(client, message.getParam()[1]);
		return;
	} else if (!channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	} else if (kickedClient == NULL || !channel->hasClient(kickedClient)) {
		reply.errUserNotInChannel(client, message.getParam()[2], channel);
		return;
	} else if (!channel->hasClient(client)) {
		reply.errNotOnChannel(client, channel);
		return;
	}
	// : <nickname> KICK <channel> <kicked nickname>
	channel->removeClient(client);
	channel->removeOperator(client);
}

void	Kick::SendMessageToClient(Client* client, Channel *channel, Client *kickedClient) {
	std::string message;

	message = ":" + client->getNickname() + " KICK ";
	message += channel->getName() + " " + kickedClient->getNickname();
	client->addWriteBuffer(message);
}