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
		selectFood(client, message.getParam()[2]);
	} else if (i == DRINK) {
		selectDrink(client);
	} else if (i == DICE) {
		rollDice(client);
	} else if (i == HOME) {
		selectTimeToGoHome(client);
	}
}

int	Bot::checkArgument(Message& message) {
	if (message.getParam().size() <= 2) return false;
	if (message.getParam()[2] == "lunch" || message.getParam()[2] == "dinner") {
		return FOOD;
	} else if (message.getParam()[2] == "drink") {
		return DRINK;
	} else if (message.getParam()[2] == "dice") {
		return DICE;
	} else if (message.getParam()[2] == "home") {
		return HOME;
	}
	return false;
}

void	Bot::whatsArgument(Client* client) {
	client->addWriteBuffer(":Bot!~Bot@" + client->getIp() + " PRIVMSG " + client->getNickname() + " :BOT!~Bot@" + client->getIp() + " need param lunch/dinner/drink/dice/home\r\n");
}

void	Bot::selectFood(Client* client, const std::string& when) {
	int random = std::rand() % 8;
	std::string menu;

	switch (random) {
		case 0:
			menu = "Chinese food";
			break;
		case 1:
			menu = "Japanese food";
			break;
		case 2:
			menu = "Meat";
			break;
		case 3:
			menu = "Western food";
			break;
		case 4:
			menu = "School food";
			break;
		case 5:
			menu = "Korean food";
			break;
		case 6:
			menu = "Chicken";
			break;
		case 7:
			menu = "Else";
			break;
	}
	std::string	tmp;
	tmp += ":Bot!~Bot@" + client->getIp() + " PRIVMSG " + client->getNickname();
	tmp += " :I Recommand you " + menu + " for " + when + "\r\n";
	client->addWriteBuffer(tmp);
}

void	Bot::selectDrink(Client* client) {
	int random = std::rand() % 8;
	std::string drink;

	switch (random) {
		case 0:
			drink = "Beer";
			break;
		case 1:
			drink = "Soju";
			break;
		case 2:
			drink = "Wine";
			break;
		case 3:
			drink = "Liquor";
			break;
		case 4:
			drink = "Cola";
			break;
		case 5:
			drink = "Sprite";
			break;
		case 6:
			drink = "Coffee";
			break;
		case 7:
			drink = "McCol/Pine bud/Ceylon tea/Thee Ja'va";
			break;
	}
	std::string	tmp;
	tmp += ":Bot!~Bot@" + client->getIp() + " PRIVMSG " + client->getNickname();
	tmp += " :I Recommand you " + drink + " to drink\r\n";
	client->addWriteBuffer(tmp);
}
void	Bot::selectTimeToGoHome(Client* client) {
	int random = std::rand() % 8;
	std::string when;

	switch (random) {
		case 0:
			when = "Right Now!!\r\n";
			break;
		case 1:
			when = "After 30 minutes\r\n";
			break;
		case 2:
			when = "After 1 hour\r\n";
			break;
		case 3:
			when = "After 2 hour\r\n";
			break;
		case 4:
			when = "After 3 hour\r\n";
			break;
		case 5:
			when = "After 4 hour\r\n";
			break;
		case 6:
			when = "Tomorrow\r\n";
			break;
		case 7:
			when = "NEVER\r\n";
			break;
	}
	std::string	tmp;
	tmp += ":Bot!~Bot@" + client->getIp() + " PRIVMSG " + client->getNickname();
	tmp += " :Let's go home " + when + "\r\n";
	client->addWriteBuffer(tmp);
}

void	Bot::rollDice(Client* client) {
	  int random = std::rand() % 101;
    std::stringstream ss;
    ss << random;
    std::string tmp;
    tmp += ":Bot!~Bot@" + client->getIp() + " PRIVMSG " + client->getNickname();
    tmp += " :Today's Number Is ";
    tmp += ss.str();
    tmp += "\r\n";
    client->addWriteBuffer(tmp);
}