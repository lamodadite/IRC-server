#include "Invite.hpp"

Invite::Invite() {}
Invite::Invite(const Invite& rhs) {(void)rhs;}
Invite& Invite::operator=(const Invite& rhs) {(void)rhs; return *this;}
Invite::~Invite() { }

void Invite::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 3) {
		reply.errNeedMoreParams(client, message.getFirstParam());
		return;
	}
	Client* invitedClient = resource.findClient(message.getParam()[1]);
	Channel* channel = resource.findChannel(message.getParam()[2]);
	if (channel == NULL) {
		reply.errNoSuchChannel(client, message.getParam()[2]);
		return;
	} else if (!channel->hasClient(client)) {
		reply.errNotOnChannel(client, channel);
		return;
	} else if (!channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	} else if (invitedClient == NULL) {
		reply.errNoSuchNick(client, message.getParam()[1]);
		return;	
	} else if (channel->hasClient(invitedClient)) {
		reply.errUserOnChannel(client, invitedClient->getNickname(), channel);
		return;
	}
	// : <nickname> INVITE <invitedNickname>
	channel->inviteClient(invitedClient);
	invitedClient->addInvitedChannel(channel);
	reply.rplInviting(client, invitedClient->getNickname(), channel);
	sendMessageToClient(client, invitedClient, channel);
}

void Invite::sendMessageToClient(Client* client, Client* invitedClient, Channel* channel) {
	std::string message;

	//:qwe!~jooh@121.135.181.42 INVITE sungyoon2 :#zxc
	message = ":" + client->getClientInfo() + " INVITE " + invitedClient->getNickname();
	message += " :" + channel->getName() + "\r\n";
	invitedClient->addWriteBuffer(message);
}