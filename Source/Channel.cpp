#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(const std::string& name): name(name), userLimit(9) {}

Channel::Channel(const Channel& rhs)
			:clientList(rhs.clientList), operatorList(rhs.operatorList),
			invitedList(rhs.invitedList), key(rhs.key), name(rhs.name),
			topic(rhs.topic), mode(rhs.mode), userLimit(rhs.userLimit) {}

Channel& Channel::operator=(const Channel& rhs) {(void)rhs; return *this;}

Channel::~Channel() {}

bool Channel::hasClient(Client* client) const {
	if (clientList.find(client) != clientList.end()) return true;
	return false;
}

bool Channel::hasOperator(Client* client) const {
	if (operatorList.find(client) != operatorList.end()) return true;
	return false;
}

void Channel::addClient(Client *client) {clientList.insert(client);}
void Channel::addOperator(Client *client) {operatorList.insert(client);}

void Channel::removeClient(Client *client) {
	std::set<Client*>::iterator it = clientList.find(client);
	if (it != clientList.end())
		clientList.erase(it);
}
void Channel::removeOperator(Client *client) {
	std::set<Client*>::iterator it = operatorList.find(client);
	if (it != operatorList.find(client))
		operatorList.erase(it);
}
void Channel::removeInvited(Client *client) {
	std::set<Client*>::iterator it = invitedList.find(client);
	if (it != invitedList.find(client))
		invitedList.erase(it);
}

const std::string& Channel::getName() const {return name;}
const std::string& Channel::getTopic() const {return topic;}
const std::string& Channel::getMode() const {return mode;}
const std::string& Channel::getKey() const {return key;}
const std::set<Client*>& Channel::getClientList() const {return clientList;}
const size_t& Channel::getUserLimit() const {return userLimit;}

void Channel::setName(const std::string& name) {this->name = name;}
void Channel::setTopic(const std::string& topic) {this->topic = topic;}
void Channel::addMode(const char mode) {
	if (this->mode.find(mode) == std::string::npos)
		this->mode += mode;
}
void Channel::removeMode(const char mode) {
	size_t pos = this->mode.find(mode);
	if (pos != std::string::npos)
		this->mode.erase(pos, 1);
}

void	Channel::setKey(const std::string& key) {this->key = key;}
void	Channel::setUserLimit(const size_t& userLimit) {this->userLimit = userLimit;}
void	Channel::removeKey() {key = "";}
void	Channel::inviteClient(Client* client) {invitedList.insert(client);}

bool	Channel::hasMode(const char mode) const {
	if (this->mode.find(mode) != std::string::npos) return true;
	return false;
}

bool	Channel::checkInvited(Client* client) const {
	if (invitedList.find(client) != invitedList.end()) return true;
	return false;
}
