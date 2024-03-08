#include "Join.hpp"

Join::Join() { }
Join::Join(const Join& rhs) { }
Join& Join::operator=(const Join& rhs) { }
Join::~Join() { }

void Join::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		//ERR_NEEDMOREPARAMS
	}
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;

	splitByComma(channels, message.getParam()[1]);
	if (message.getParam().size() >= 3)
		splitByComma(keys, message.getParam()[2]);
	// client가 들어갈 수 있는 채널수 제한이 있을 경우 제한에 관한 처리
	
	for (size_t i = 0; i < channels.size(); i++) {
		Channel* channel = resource.findChannel(channels[i]);
		if (channel == 0) {
			if ((channels[i][0] != '#' && channels[i][0] != '&') || hasControlG(channels[i])) {
				continue; //ERR_BADCHANMASK
			}
			resource.addChannel(channels[i]);
			channel = resource.findChannel(channels[i]);
			if (i < keys.size()) channel->setKey(keys[i]);
		} else {
			if (channel->getKey().size() && i < keys.size() && channel->getKey() != keys[i]) {
				continue; //ERR_BADCHANNELKEY
			}
			if (channel->getClientList().size() == channel->getUserLimit()) {
				continue; //ERR_CHANNELISFULL
			}
			if (channel->hasMode('i') && !channel->checkInvited(client)) {
				continue; //ERR_INVITEONLYCHAN
			}
			if ((channels[i][0] != '#' && channels[i][0] != '&') || hasControlG(channels[i])) {
				continue; //ERR_BADCHANMASK
			}
		}
		channel->addClient(client);
		client->addJoinedChannel(channel);
		sendMessageToChannel(channel, client->getNickname() 
				+ " is joining the channel " + channels[i] + '\n');
		if (channel->getTopic().size()) ;//RPL_TOPIC
	}
}

void	Join::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	int					index;

	while ((index = param.find(',')) != std::string::npos) {
		tmp = param.substr(0, index);
		target.push_back(tmp);
		param.erase(0, index + 2);
	}
	if (param.size()) target.push_back(param);
}

void	Join::sendMessageToChannel(Channel* channel, std::string message) {
	const std::set<Client*>& clientList = channel->getClientList();

	std::set<Client*>::iterator iter;
	for (iter = clientList.begin(); iter != clientList.end(); iter++) {
		(*iter)->addWriteBuffer(message);
	}
}

bool	Join::hasControlG(std::string param) {
	for (size_t i = 0; i < param.size(); i++)
		if (param[i] == '^G') return true;
	return false;
}