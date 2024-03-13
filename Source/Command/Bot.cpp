#include "Bot.hpp"

Bot::Bot() {}
Bot::Bot(const Bot& rhs) {(void)rhs;}
Bot& Bot::operator=(const Bot& rhs) {(void)rhs; return *this;}
Bot::~Bot() {}

void	Bot::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());

	int i = checkArgument(message);
	if (i == 0) {
		whatsArgument(client);
	}
}

int	Bot::checkArgument(Message message) {
	int i = 0;
	if (message.getParam().size() == 1) return i;

}

void	Bot::whatsArgument(Client* client) {
	client->addWriteBuffer("");
}