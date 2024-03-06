#include "Nick.hpp"

Nick::Nick() { }
Nick::Nick(const Nick& rhs) { }
Nick& Nick::operator=(const Nick& rhs) { }
Nick::~Nick() { }

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
	return true;
}

void Nick::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		// ERR_NONICKNAMEGIVEN;
		return ;
	} else if (resource.findClient(message.getParam()[1]) == NULL) {
		// ERR_NICKNAMEINUSE;
		return ;
	} else if (!isValidNickname(message.getParam()[1])) {
		// ERR_ERRONEUSNICKNAME;
		return ;
	}
	client->setOldNickname(client->getNickname());
	client->setNickname(message.getParam()[1]);
	if (client->getRegistered()) {
		// : <oldNickname> NICK <nickname>
	} else if (client->canBeRegistered()) {
		fillWithWelcomeMessage(client);
	}
}

void	Nick::fillWithWelcomeMessage(Client* client) {
	
}