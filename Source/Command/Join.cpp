#include "Join.hpp"

Join::Join() {}
Join::Join(const Join& rhs) {(void)rhs;}
Join& Join::operator=(const Join& rhs) {(void)rhs; return *this;}
Join::~Join() {}

void Join::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 2) {
		reply.errNeedMoreParams(client, message.getFirstParam());
		return;
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
			if ((channels[i][0] != '#' && channels[i][0] != '&')) {
			//if ((channels[i][0] != '#' && channels[i][0] != '&') || hasControlG(channels[i])) {
				reply.errBadChanMask(client);
				continue;
			}
			resource.addChannel(channels[i]);
			channel = resource.findChannel(channels[i]);
			if (i < keys.size()) channel->setKey(keys[i]);
		} else {
			if (channel->getKey().size() && i < keys.size() && channel->getKey() != keys[i]) {
				reply.errBadChannelKey(client, channel);
				continue;
			}
			if (channel->getClientList().size() == channel->getUserLimit()) {
				reply.errChannelIsFull(client, channel);
				continue;				
			}
			if (channel->hasMode('i') && !channel->checkInvited(client)) {
				reply.errInviteOnlyChan(client, channel);
				continue;
			}
			if ((channels[i][0] != '#' && channels[i][0] != '&')) {
			//if ((channels[i][0] != '#' && channels[i][0] != '&') || hasControlG(channels[i])) {
				reply.errBadChanMask(client);
				continue;
			}
		}
		channel->addClient(client);
		client->addJoinedChannel(channel);
		sendMessageToChannel(channel, client->getNickname() 
				+ " is joining the channel " + channels[i] + '\n', client);
		if (channel->getTopic().size()) reply.rplTopic(client, channel);
	}
}

void	Join::splitByComma(std::vector<std::string>& target, std::string param) {
	std::string	tmp;
	size_t					index;

	while ((index = param.find(',')) != std::string::npos) {
		tmp = param.substr(0, index);
		target.push_back(tmp);
		param.erase(0, index + 2);
	}
	if (param.size()) target.push_back(param);
}

void	Join::sendMessageToChannel(Channel* channel, std::string message, Client* client) {
	const std::set<Client*>& clientList = channel->getClientList();
	(void)message;
	std::set<Client*>::iterator iter;
	message = "";
	client->addWriteBuffer(":" + client->getNickname() + " JOIN " + channel->getName() + "\r\n");
	for (iter = clientList.begin(); iter != clientList.end(); iter++) {
		if ((*iter)->getNickname() != client->getNickname()) {
			(*iter)->addWriteBuffer(":" + client->getNickname() + " JOIN " + channel->getName() + "\r\n");
			std::cout << ":" + client->getNickname() + " JOIN " + channel->getName() << "\r\n";
		}
		message += "@" + (*iter)->getNickname() + " ";
	}
	client->addWriteBuffer(":IRC_Server 353 " + client->getNickname() + " @ " + channel->getName() + " :");
	client->addWriteBuffer(message + "\r\n");
	client->addWriteBuffer(":IRC_Server 366 " + client->getNickname() + " " + channel->getName() + " :End of /NAMES list\r\n");
	std::cout << ":IRC_Server 353 " + client->getNickname() + " @ " + channel->getName() + " :" + message << '\n';
	std::cout << ":IRC_Server 366 " + client->getNickname() + " " + channel->getName() + " :End of /NAMES list\n";
}

// TODO: 시그널 처리 해야함
// bool	Join::hasControlG(std::string param) {
// 	for (size_t i = 0; i < param.size(); i++)
// 		if (param[i] == '^G') return true;
// 	return false;
// }