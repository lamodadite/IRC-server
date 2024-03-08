#include "Topic.hpp"

Topic::Topic() { }
Topic::Topic(const Topic& rhs) { }
Topic& Topic::operator=(const Topic& rhs) { }
Topic::~Topic() { }

void Topic::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (message.getParam().size() < 2) {
		//ERR_NEEDMOREPARAMS
		return;
	}
	Channel* channel = resource.findChannel(message.getParam()[1]);
	if (!channel) {
		//ERR_NOSUCHCHANNEL
		return;
	} else if (!channel->hasClient(client)) {
		//ERR_NOTONCHANNEL
		return;
	} else if (channel->hasMode('t') && !channel->hasOperator(client)) {
		//ERR_CHANOPRIVSNEEDED
		return;
	}
	if (message.getParam().size() == 2) {
		if (channel->getTopic() == "") {

		} else {
			channel->setTopic("");

		}
	}	else {
		if (channel->getTopic() == message.getParam()[2]) {

		} else {
			channel->setTopic(message.getParam()[2]);

		}	
	}
}

void	Topic::sendMessageToChannel(Channel* channel, std::string message) {
	const std::set<Client*>& clientList = channel->getClientList();

	std::set<Client*>::iterator iter;
	for (iter = clientList.begin(); iter != clientList.end(); iter++) {
		(*iter)->addWriteBuffer(message);
	}
}