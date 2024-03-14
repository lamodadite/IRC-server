#include "Topic.hpp"

Topic::Topic() {}
Topic::Topic(const Topic& rhs) : Command(rhs) {(void)rhs;}
Topic& Topic::operator=(const Topic& rhs) {(void)rhs;return *this;}
Topic::~Topic() {}

void Topic::execute(Resource& resource, Message message) {
	Client*	client = resource.findClient(message.getClientFd());

	if (!client->getRegistered()) return;
	if (message.getParam().size() < 2) {
		reply.errNeedMoreParams(client, message.getFirstParam());
		return;
	}
	Channel* channel = resource.findChannel(message.getParam()[1]);
	if (!channel) {
		reply.errNoSuchChannel(client, message.getParam()[1]);
		return;
	} else if (!channel->hasClient(client)) {
		reply.errNotOnChannel(client, channel);
		return;
	} else if (channel->hasMode('t') && !channel->hasOperator(client)) {
		reply.errChanOperIvsNeeded(client, channel);
		return;
	}  
	if (message.getParam().size() == 2) {
		if (channel->getTopic() == "") {
			reply.rplNoTopic(client, channel);
		} else {
			reply.rplTopic(client, channel);
			reply.rplTopicWhoTime(client, channel);
		}
		return;
	} else {
		channel->setTopic(message.getParam()[2]);
		channel->setTopicAuthor(client->getClientInfo());
		std::stringstream ss;
		ss << std::time(NULL);
		channel->setTopicSetTime(ss.str());
	}
	sendMessageToChannel(client, channel);
}

void	Topic::sendMessageToChannel(Client* client, Channel* channel) {
	const std::set<Client*>& clientList = channel->getClientList();
	std::string message = ":" + client->getClientInfo() + " TOPIC " + channel->getName() + " :" + channel->getTopic() + "\r\n";
	std::set<Client*>::iterator iter;

	for (iter = clientList.begin(); iter != clientList.end(); iter++) {
		(*iter)->addWriteBuffer(message);
	}
}