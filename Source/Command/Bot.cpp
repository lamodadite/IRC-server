#include "Bot.hpp"

Bot::Bot() {}
Bot::Bot(const Bot& rhs) {(void)rhs;}
Bot& Bot::operator=(const Bot& rhs) {(void)rhs; return *this;}
Bot::~Bot() {}

void	Bot::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());

	int i = checkArgument(message);
	if (i == false) {
		whatsArgument(client);
	} else if (i == FOOD) {
		selectFood(client);
	} else if (i == DRINK) {
		selectDrink(client);
	} else if (i == DICE) {
		rollDice(client);
	} else if (i == HOME) {
		selectTimeToGoHome(client);
	}
}

int	Bot::checkArgument(Message message) {
	int i = false;
	if (message.getParam().size() == 1) return false;
	if (message.getParam()[1] == "lunch", message.getParam()[1] == "dinner") {
		return FOOD;
	} else if (message.getParam()[1] == "drink") {
		return DRINK;
	} else if (message.getParam()[1] == "dice") {
		return DICE;
	} else if (message.getParam()[1] == "home") {
		return HOME;
	}
}

void	Bot::whatsArgument(Client* client) {
	client->addWriteBuffer(client->getClientInfo() + );
}