#include "User.hpp"

User::User() { }
User::User(const User& rhs) { }
User& User::operator=(const User& rhs) { }
User::~User() { }

void User::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());
	
	if (message.getParam().size() < 5) {
		// ERR_NEEDMOREPARAMS
		return ;
	} else if (client->getRegistered()) {
		// ERR_ALREADYREGISTERED
	}
	client->setUsername(message.getParam()[1]);
	if (client->canBeRegistered())
		fillWithWelcomeMessage(client);
}

void	User::fillWithWelcomeMessage(Client* client) {
	
}