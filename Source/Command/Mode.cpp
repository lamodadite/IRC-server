#include "Mode.hpp"

Mode::Mode() {}
Mode::Mode(const Mode& rhs) {(void)rhs;}
Mode& Mode::operator=(const Mode& rhs) {(void)rhs; return *this;}
Mode::~Mode() {}

void	Mode::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 2) {
		reply.errNeedMoreParams(client, message.getFirstParam());
		return ;
	}
	if (message.getParam()[1][0] != '#' && message.getParam()[1][0] != '&')
		return ;
	Channel* channel = resource.findChannel(message.getParam()[1]);
	if (channel == NULL) {
		reply.errNoSuchChannel(client, message.getParam()[1]);
		return;
	}
	if (message.getParam().size() < 3) {
		// reply.rplChannelModeIs(client, channel);
		// reply.rplCreationTime(client, channel);
		return;
	}
	if (!channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	}
	
	int flag = 0;
	int arguments = 0;
	const std::string& modestring = message.getParam()[2];
	for (size_t i = 0; i < modestring.size(); i++) {
		if (modestring[i] == '-') flag = -1;
		else if (modestring[i] == '+') flag = +1;
		if (flag = 0) continue;
		if (modestring[i] == 'o') arguments++;
		if (flag == 1 && (modestring[i] == 'k' || modestring[i] == 'l')) arguments++;
	}
	if (message.getParam().size() != 3 + arguments) return;
	
	flag = 0;
	int index = 3;
	for (size_t i = 0; i < modestring.size(); i++) {
		if (modestring[i] == '-') flag = -1;
		else if (modestring[i] == '+') flag = +1;
		if (flag = 0) continue;
		if (modestring[i] == 'i') changeModeI(channel, flag);
		else if (modestring[i] == 't') changeModeT(channel, flag);
		else if (modestring[i] == 'k') changeModeK(channel, flag, index, message);
		else if (modestring[i] == 'o') changeModeO(channel, resource, flag, index, message);
		else if (modestring[i] == 'l') changeModeL(channel, flag, index, message);
	}	
}

void	Mode::changeModeI(Channel* channel, int flag) {
	if (flag == -1) channel->removeMode('i');
	else if (flag == 1) channel->addMode('i');
}

void	Mode::changeModeT(Channel* channel, int flag) {
	if (flag == -1) channel->removeMode('t');
	else if (flag == 1) channel->addMode('t');
}

void	Mode::changeModeK(Channel* channel, int flag, int& index, Message message) {
	if (flag == -1) {
		channel->removeMode('k');
		channel->removeKey();
	} else {
		std::string argument = message.getParam()[index];
		channel->addMode('k');
		channel->setKey(argument);
		index++;
	}
}

void	Mode::changeModeO(Channel* channel, Resource& resource, int flag, int& index, Message message) {
	std::string argument = message.getParam()[index];
	Client* client = resource.findClient(argument);
	index++;
	if (!client || !channel->hasOperator(client)) return;
	if (flag == -1) channel->removeOperator(client);
	else channel->addOperator(client);
}

void	Mode::changeModeL(Channel* channel, int flag, int& index, Message message) {
	if (flag == -1) {
		channel->setUserLimit(0);
		channel->removeMode('l');
	}	else {
		std::string argument = message.getParam()[index];
		index++;
		long tmp = std::strtol(argument.c_str(), NULL, 10);
		if (errno == ERANGE || tmp < 0 || tmp > 2147483647) return;
		channel->setUserLimit(static_cast<int>(tmp));
		channel->addMode('l');
	}
}