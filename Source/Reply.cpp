#include "Reply.hpp"

Reply::Reply() {}
Reply::Reply(const Reply& rhs) {}
Reply& Reply::operator=(const Reply& rhs) {}
Reply::~Reply() {}

void	Reply::errNeedMoreParams(Client* client, const std::string command) {
	std::string	buffer;

	buffer += "461 " + client->getNickname() + ' ' + command + " :Not enough parameters\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errAlreadyRegistered(Client* client) {
	std::string	buffer;

	buffer += "462 " + client->getNickname() + " :You may mot reregister\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errPasswdMisMatch(Client* client) {
	std::string	buffer;

	buffer += "464 " + client->getNickname() + " :Password incorrect\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoNicknameGiven(Client* client) {
	std::string	buffer;

	buffer += "431 " + client->getNickname() + " :No nickname given\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errErroneusNickname(Client* client) {
	std::string	buffer;

	buffer += "432 " + client->getNickname() + ' ' + client->getNickname() + " :Erroneus nickname\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNicknameInUse(Client* client) {
	std::string	buffer;

	buffer += "433 " + client->getNickname() + ' ' + client->getNickname() + " :Nickname is already in use\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoSuchChannel(Client* client, std::string channel) {
	std::string	buffer;

	buffer += "403 " + client->getNickname() + ' ' + channel + " :No such channel\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errTooManyChannel(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "405 " + client->getNickname() + ' ' + channel->getName() + " :You have joined too many channel\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errBadChannelKey(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "475 " + client->getNickname() + ' ' + channel->getName() + " :Cannot join channel (+k)\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errChannelIsFull(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "471 " + client->getNickname() + ' ' + channel->getName() + " :Cannot join channel (+l)\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errInviteOnlyChan(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "473 " + client->getNickname() + ' ' + channel->getName() + " :Cannot join channel (+i)\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errBadChanMask(Client* client) {
	std::string	buffer;

	buffer += "476 " + client->getNickname() + " :Bad Channel Mask\n";
	client->addWriteBuffer(buffer);
}

void	Reply::rplTopic(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "332 " + client->getNickname() + ' ' + channel->getName() + " :" + channel->getTopic() + '\n';
	client->addWriteBuffer(buffer);
}

// void	Reply::rplTopicWhoTime(Client* client, Channel* channel) {
// 	std::string	buffer;

// 	buffer += "333 " + client->getNickname() + ' ' + channel->getName() + ' ' + channel->getTopicAuthor() + ' ' + channel->getTopicSetTime() + '\n';
// 	client->addWriteBuffer(buffer);
// }

void	Reply::errNotOnChannel(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "442 " + client->getNickname() + ' ' + channel->getName() + " :You're not on channel\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errChanOperIvsNeeded(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "482 " + client->getNickname() + ' ' + channel->getName() + " :You're not channel operator\n";
	client->addWriteBuffer(buffer);
}

void	Reply::rplNoTopic(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "331 " + client->getNickname() + ' ' + channel->getName() + " :No topic is set\n";
	client->addWriteBuffer(buffer);
}

void	Reply::rplInviting(Client* client, std::string nick, Channel* channel) {
	std::string	buffer;

	buffer += "341 " + client->getNickname() + ' ' + nick + ' ' + channel->getName() + '\n';
	client->addWriteBuffer(buffer);
}

void	Reply::errUserOnChannel(Client* client, std::string nick, Channel* channel) {
	std::string	buffer;

	buffer += "443 " + client->getNickname() + ' ' + nick + ' ' + channel->getName() + " :is already on channel\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errUserNotInChannel(Client* client, std::string nick, Channel* channel) {
	std::string	buffer;

	buffer += "441 " + client->getNickname() + ' ' + nick + ' ' + channel->getName() + " :They aren`t on that channel\n";
	client->addWriteBuffer(buffer);
}

// void	Reply::rplChannelModeIs(Client* client, Channel* channel) {}

// void	Reply::rplCreationTime(Client* client, Channel* channel) {
// 	std::string	buffer;

// 	buffer += "329 " + client->getNickname() + ' ' + channel->getName() + ' ' + channel->getCreationTime() + '\n';
// 	client->addWriteBuffer(buffer);
// }

void	Reply::errNoSuchNick(Client* client, std::string nickname) {
	std::string	buffer;

	buffer += "401 " + client->getNickname() + ' ' + nickname + " :No such nick/channel\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errCannotSendToChan(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += "404 " + client->getNickname() + ' ' + channel->getName() + " :Cannot send to channel\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoRecipient(Client* client, const std::string& command) {
	std::string	buffer;

	buffer += "411 " + client->getNickname() + " :No recipient given (" + command + ")\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoTextToSend(Client* client) {
	std::string	buffer;

	buffer += "412 " + client->getNickname() + " :No text to send\n";
	client->addWriteBuffer(buffer);
}