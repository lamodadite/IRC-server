#include "Mode.hpp"

Mode::Mode() { }
Mode::Mode(const Mode& rhs) { }
Mode& Mode::operator=(const Mode& rhs) { }
Mode::~Mode() { }

void Mode::parseModeString(Message &message) {
	const std::vector<std::string>& param = message.getParam();

	for (size_t i = 2; i < param.size(); i++) {
		if (param[i][0] == '+' || param[i][0] == '-') {
			
		}
	}
}

void Mode::execute(Resource& resource, Message message) {
	if (message.getParam().size() < 2) {
		return ;
	}
	Channel* channel = resource.findChannel(message.getParam()[1]);
	if (channel == NULL) {
		// ERR_NOSUCHCHANNEL
		return;
	}
	if (message.getParam().size() < 3) {
		// RPL_CHANNELMODEIS
		// RPL_CREATIONTIME
		return;
	}
	Client* client = resource.findClient(message.getClientFd());
	if (!channel->hasOperator(client)) {
		// ERR_CHANOPRIVSNEEDED
		return;
	}
	// i, t, k, o, l
	// :<nickname> MODE <channel>
}