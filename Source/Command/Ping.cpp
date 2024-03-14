#include "Ping.hpp"

Ping::Ping() {}
Ping::Ping(const Ping& rhs) : Command(rhs) {(void)rhs;}
Ping& Ping::operator=(const Ping& rhs) {(void)rhs;return *this;}
Ping::~Ping() {}

void	Ping::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		return ;
	} else if (!client->getRegistered()) {
		return ;
	}
	SendMessageToClient(client);
}

void	Ping::SendMessageToClient(Client* target) {
	std::string message;
	
	message = "PONG IRC_Server\r\n";
	target->addWriteBuffer(message);
}
