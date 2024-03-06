#include "Kick.hpp"

Kick::Kick() { }
Kick::Kick(const Kick& rhs) { }
Kick& Kick::operator=(const Kick& rhs) { }
Kick::~Kick() { }

void Kick::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());
	Channel* channel;
	Client* kickedClient;

	if (message.getParam().size() < 3) {
		// ERR_NEEDMOREPARAMS
		return;
	}
	channel = resource.findChannel(message.getParam()[1]);
	kickedClient = resource.findClient(message.getParam()[2]);

	if (channel == NULL) {
		// ERR_NOSUCHCHANNEL
		return;
	} else if (!channel->hasOperator(client)) {
		// ERR_CHANOPRIVSNEEDED
		return;
	} else if (kickedClient == NULL || !channel->hasClient(kickedClient)) {
		// ERR_USERNOTINCHANNEL
		return;
	} else if (!channel->hasClient(client)) {
		// ERR_NOTONCHANNEL
		return;
	}
	// : <nickname> KICK <channel> <kicked nickname>
	channel->removeClient(client);
	channel->removeOperator(client);
}