#include "Reply.hpp"
#include "Resource.hpp"

Reply::Reply() {}
Reply::Reply(const Reply& rhs) {(void)rhs;}
Reply& Reply::operator=(const Reply& rhs) {(void)rhs; return *this;}
Reply::~Reply() {}

void	Reply::errNeedMoreParams(Client* client, const std::string& command) {
	std::string	buffer;

	buffer += ":IRC_Server 461 " + client->getNickname() + ' ' + command + " :Not enough parameters\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errAlreadyRegistered(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 462 " + client->getNickname() + " :You may mot reregister\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errPasswdMisMatch(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 464 " + client->getNickname() + " :Password incorrect\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoNicknameGiven(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 431 " + client->getNickname() + " :No nickname given\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errErroneusNickname(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 432 " + client->getNickname() + ' ' + client->getNickname() + " :Erroneus nickname\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNicknameInUse(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 433 " + client->getNickname() + ' ' + client->getNickname() + " :Nickname is already in use\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoSuchChannel(Client* client, std::string channel) {
	std::string	buffer;

	buffer += ":IRC_Server 403 " + client->getNickname() + ' ' + channel + " :No such channel\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errTooManyChannel(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 405 " + client->getNickname() + ' ' + channel->getName() + " :You have joined too many channel\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errBadChannelKey(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 475 " + client->getNickname() + ' ' + channel->getName() + " :Cannot join channel (+k)\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errChannelIsFull(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 471 " + client->getNickname() + ' ' + channel->getName() + " :Cannot join channel (+l)\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errInviteOnlyChan(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 473 " + client->getNickname() + ' ' + channel->getName() + " :Cannot join channel (+i)\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errBadChanMask(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 476 " + client->getNickname() + " :Bad Channel Mask\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::rplTopic(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 332 " + client->getNickname() + ' ' + channel->getName() + " :" + channel->getTopic() + "\r\n";
	client->addWriteBuffer(buffer);
}

// void	Reply::rplTopicWhoTime(Client* client, Channel* channel) {
// 	std::string	buffer;

// 	buffer += ":IRC_Server 333 " + client->getNickname() + ' ' + channel->getName() + ' ' + channel->getTopicAuthor() + ' ' + channel->getTopicSetTime() + "\r\n";
// 	client->addWriteBuffer(buffer);
// }

void	Reply::errNotOnChannel(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 442 " + client->getNickname() + ' ' + channel->getName() + " :You're not on channel\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errChanOperIvsNeeded(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 482 " + client->getNickname() + ' ' + channel->getName() + " :You're not channel operator\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::rplNoTopic(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 331 " + client->getNickname() + ' ' + channel->getName() + " :No topic is set\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::rplInviting(Client* client, std::string nick, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 341 " + client->getNickname() + ' ' + nick + ' ' + channel->getName() + "\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errUserOnChannel(Client* client, std::string nick, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 443 " + client->getNickname() + ' ' + nick + ' ' + channel->getName() + " :is already on channel\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errUserNotInChannel(Client* client, std::string nick, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 441 " + client->getNickname() + ' ' + nick + ' ' + channel->getName() + " :They aren`t on that channel\r\n";
	client->addWriteBuffer(buffer);
}

// void	Reply::rplChannelModeIs(Client* client, Channel* channel) {}

// void	Reply::rplCreationTime(Client* client, Channel* channel) {
// 	std::string	buffer;

// 	buffer += ":IRC_Server 329 " + client->getNickname() + ' ' + channel->getName() + ' ' + channel->getCreationTime() + "\r\n";
// 	client->addWriteBuffer(buffer);
// }

void	Reply::errNoSuchNick(Client* client, std::string nickname) {
	std::string	buffer;

	buffer += ":IRC_Server 401 " + client->getNickname() + ' ' + nickname + " :No such nick/channel\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errCannotSendToChan(Client* client, Channel* channel) {
	std::string	buffer;

	buffer += ":IRC_Server 404 " + client->getNickname() + ' ' + channel->getName() + " :Cannot send to channel\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoRecipient(Client* client, const std::string& command) {
	std::string	buffer;

	buffer += ":IRC_Server 411 " + client->getNickname() + " :No recipient given (" + command + ")\r\n";
	client->addWriteBuffer(buffer);
}

void	Reply::errNoTextToSend(Client* client) {
	std::string	buffer;

	buffer += ":IRC_Server 412 " + client->getNickname() + " :No text to send\r\n";
	client->addWriteBuffer(buffer);
}