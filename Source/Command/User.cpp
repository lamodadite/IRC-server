#include "User.hpp"

User::User() { }
User::User(const User& rhs) : Command(rhs) {(void) rhs;}
User& User::operator=(const User& rhs) {(void)rhs; return *this;}
User::~User() { }

void User::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());
	
	if (!client->getPassed()) {
		return ;
	} else if (message.getParam().size() < 5) {
		reply.errNeedMoreParams(client, message.getFirstParam());
		return ;
	} else if (client->getRegistered()) {
		reply.errAlreadyRegistered(client);
		return ;
	}
	client->setUsername(message.getParam()[1]);
	client->setIp(message.getParam()[3]);
	if (client->canBeRegistered()) {
		reply.rplWelcomeMessage(client);
	}
}