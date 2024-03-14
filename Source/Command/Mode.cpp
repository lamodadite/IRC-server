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
		reply.rplChannelModeIs(client, channel);
		reply.rplCreationTime(client, channel);
		return;
	}
	if (!channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	}
	
	bool	flag = true;
	int		arguments = 0;
	std::string modestring = message.getParam()[2];
	for (size_t i = 0; i < modestring.size(); i++) {
		if (modestring[i] == '-') {
			flag = false;
			continue;
		}	else if (modestring[i] == '+') {
			flag = true;
			continue;
		} else if (modestring[i] != 'i' && modestring[i] != 't'
			&& modestring[i] != 'k' && modestring[i] != 'o' && modestring[i] != 'l') {
			modestring[i] = 7;
			continue;
		}
		if (modestring[i] == 'o') arguments++;
		if (flag == true && (modestring[i] == 'k' || modestring[i] == 'l')) arguments++;
	}
	if (message.getParam().size() != static_cast<size_t>(3 + arguments)) return;
	flag = true;
	int index = 3;
	std::set<int> notValidArgument;
	for (size_t i = 0; i < modestring.size(); i++) {
		if (modestring[i] == '-') flag = false;
		else if (modestring[i] == '+') flag = true;
		if (modestring[i] == 7) continue;
		if (modestring[i] == 'i') {
			if (changeModeI(channel, flag)) modestring[i] = 7;
		} else if (modestring[i] == 't') {
			if (changeModeT(channel, flag))	modestring[i] = 7;
		} else if (modestring[i] == 'k') {
			if (changeModeK(channel, flag, index, message)) modestring[i] = 7;
		} else if (modestring[i] == 'o') {
			if (changeModeO(channel, resource, flag, index, message)) {
				modestring[i] = 7;
				notValidArgument.insert(index - 1);
			}
		} else if (modestring[i] == 'l') {
			int tmp = changeModeL(channel, flag, index, message);
			if (tmp == 1) {
				modestring[i] = 7;
			} else if (tmp == 2) {
				modestring[i] = 7;
				notValidArgument.insert(index - 1);
			}
		}
	}
	std::string replyMessage;
	std::string tmp = deleteFailedMode(modestring);
	if (!tmp.size()) return;
	replyMessage += ":" + client->getClientInfo();
	for (size_t i = 0; i < message.getParam().size(); i++) {
		if (i == 2) replyMessage += ' ' + tmp;
		else if (notValidArgument.find(i) != notValidArgument.end()) continue;
		else replyMessage += ' ' + message.getParam()[i];
	}
	replyMessage += "\r\n";
	sendMessageToChannel(channel, replyMessage);
}

const std::string	Mode::deleteFailedMode(std::string& modestring) {
	int flag = 1;
	std::string	tmp;

	for (size_t i = 0; i < modestring.size(); i++) {
		if (modestring[i] == 7) continue;
		if (modestring[i] == '-') flag = -1;
		else if (modestring[i] == '+') flag = 1;
		else {
			if (flag == 0) tmp += modestring[i];
			else if (flag == -1) {
				tmp += '-'; 
				tmp += modestring[i];
				flag = 0;
			} else if (flag == 1) {
				tmp += '+';
				tmp += modestring[i];
				flag = 0;
			}
		}
	}
	return tmp;
}

void	Mode::sendMessageToChannel(Channel* channel, std::string& replyMessage) {
	const std::set<Client*>& clientList = channel->getClientList();
	std::set<Client*>::iterator iter;
	
	
	for (iter = clientList.begin(); iter != clientList.end(); iter++) {
		(*iter)->addWriteBuffer(replyMessage);
	}
}

bool	Mode::changeModeI(Channel* channel, bool flag) {
	if (flag == false) {
		if (!channel->hasMode('i')) return true;
		channel->removeMode('i');
	}
	else if (flag == true) {
		if (channel->hasMode('i')) return true;
		channel->addMode('i');
	}
	return false;
}

bool	Mode::changeModeT(Channel* channel, bool flag) {
	if (flag == false) {
		if (!channel->hasMode('t')) return true;
		channel->removeMode('t');
	}
	else if (flag == true) {
		if (channel->hasMode('t')) return true;
		channel->addMode('t');
	}
	return false;
}

bool	Mode::changeModeK(Channel* channel, bool flag, int& index, Message message) {
	if (flag == false) {
		if (!channel->hasMode('k')) return true;
		channel->removeMode('k');
		channel->removeKey();
	} else {
		std::string argument = message.getParam()[index];
		channel->addMode('k');
		channel->setKey(argument);
		index++;
	}
	return false;
}

bool	Mode::changeModeO(Channel* channel, Resource& resource, bool flag, int& index, Message message) {
	std::string argument = message.getParam()[index];
	Client* client = resource.findClient(argument);
	index++;
	if (!client) return true;
	if (flag == false) channel->removeOperator(client);
	else channel->addOperator(client);
	return false;
}

int	Mode::changeModeL(Channel* channel, bool flag, int& index, Message message) {
	if (flag == false) {
		if (!channel->hasMode('l')) return 1;
		channel->setUserLimit(0);
		channel->removeMode('l');
	}	else {
		std::string argument = message.getParam()[index];
		index++;
		long tmp = std::strtol(argument.c_str(), NULL, 10);
		if (errno == ERANGE || tmp <= 0 || tmp > 2147483647) return 2;
		channel->setUserLimit(static_cast<int>(tmp));
		channel->addMode('l');
	}
	return (0);
}