#include "Mode.hpp"

Mode::Mode() { }
Mode::Mode(const Mode& rhs) {(void)rhs;}
Mode& Mode::operator=(const Mode& rhs) {(void)rhs; return *this;}
Mode::~Mode() {}

void Mode::parseModeString(Channel& channel, Message &message) {
	const std::vector<std::string>& param = message.getParam();
	(void)channel;
	// [<modestring> [<mode arguments] ...]
	// i, t, k, o, l
	// MODE +kl asd 15
	// MODE +k asd +l 1

	// modestring과 argument를 나눈다.
	std::vector<std::string> modestring;
	std::vector<std::string> argument;

	for (size_t i = 2; i < param.size(); i++) {
		if (param[i].size() > 0 && (param[i][0] == '+' || param[i][1] == '-'))
			modestring.push_back(param[i]);
		else
			argument.push_back(param[i]);
	}

	//size_t argumentIndex = 0;
	for (size_t i = 0; i < modestring.size(); i++) {
		//int addFlag = modestring[i][0] == '+' ? 1 : 0;
		for (size_t j = 1; j < modestring[i].size(); j++) {
			
		}
	}
}

void Mode::execute(Resource& resource, Message message) {
	Client* client = resource.findClient(message.getClientFd());

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 2) {
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
		//reply.rplChannelModeIs()// RPL_CHANNELMODEIS
		// RPL_CREATIONTIME
		return;
	}
	if (!channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	}
	// :<nickname> MODE <channel>
}