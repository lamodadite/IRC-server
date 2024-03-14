#include "Nick.hpp"

Nick::Nick() {}
Nick::Nick(const Nick& rhs) : Command(rhs) {(void)rhs;}
Nick& Nick::operator=(const Nick& rhs) {(void)rhs; return *this;}
Nick::~Nick() {}

bool Nick::isValidNickname(const std::string& nickname) const
{
	if (nickname.empty())
		return false;
	else if (nickname[0] == '$' || nickname[0] == ':' ||
			nickname[0] == '#' || nickname[0] == '&')
		return false;
	else if (nickname.find(",") != std::string::npos)
		return false;
	else if (nickname.find("*") != std::string::npos)
		return false;
	else if (nickname.find(" ") != std::string::npos)
		return false;
	else if (nickname.find("?") != std::string::npos)
		return false;
	else if (nickname.find("!") != std::string::npos)
		return false;
	else if (nickname.find("@") != std::string::npos)
		return false;
	else if (nickname == "Bot")
		return false;
	return true;
}

void Nick::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		reply.errNoNicknameGiven(client);
		return ;
	} else if (resource.findClient(message.getParam()[1]) != NULL) {
		client->setNickname(message.getParam()[1], false);
		reply.errNicknameInUse(client);
		return ;
	} else if (!isValidNickname(message.getParam()[1])) {
		reply.errErroneusNickname(client);
		return ;
	}
	client->setOldNickname(client->getNickname());
	client->setNickname(message.getParam()[1]);
	if (client->getRegistered()) {
		SendMessageToClient(client);
	}
	else if (client->canBeRegistered()) {
		reply.rplWelcomeMessage(client);
	}
}

void	Nick::SendMessageToClient(Client* client) {
	std::string message;
	
	message = ":" + client->getClientInfo(true);
	message += " NICK " + client->getNickname() + "\r\n";
	client->addWriteBuffer(message);
}
