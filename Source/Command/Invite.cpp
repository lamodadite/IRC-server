#include "Invite.hpp"

Invite::Invite() { }
Invite::Invite(const Invite& rhs) { }
Invite& Invite::operator=(const Invite& rhs) { }
Invite::~Invite() { }

void Invite::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 3) {
		// ERR_NEEDMOREPARAMS
		return;
	}
	Client* invitedClient = resource.findClient(message.getParam()[1]);
	Channel* channel = resource.findChannel(message.getParam()[2]);
	if (channel == NULL) {
		// ERR_NOSUCHCHANNEL
		return;
	} else if (!channel->hasClient(client)) {
		// ERR_NOTONCHANNEL
		return;
	} else if (!channel->hasOperator(client)) {
		// ERR_CHANOPRIVSNEEDED
		return;
	} else if (!channel->hasClient(invitedClient)) {
		// ERR_USERONCHANNEL
		return;
	}
	// : <nickname> INVITE <invitedNickname>
	channel->inviteClient(invitedClient);
}