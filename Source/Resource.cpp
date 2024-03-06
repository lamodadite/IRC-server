#include "Resource.hpp"

Resource::Resource() {
	commandMap.insert(std::make_pair("NICK", new Nick()));
	commandMap.insert(std::make_pair("INVITE", new Invite()));
	commandMap.insert(std::make_pair("JOIN", new Join()));
	commandMap.insert(std::make_pair("KICK", new Kick()));
	commandMap.insert(std::make_pair("MODE", new Mode()));
	commandMap.insert(std::make_pair("PASS", new Pass()));
	commandMap.insert(std::make_pair("TOPIC", new Topic()));
	commandMap.insert(std::make_pair("USER", new User()));
	commandMap.insert(std::make_pair("PRIVMSG", new Privmsg()));
}

Resource::~Resource() {
	for (std::map<std::string, Command*>::iterator it = commandMap.begin(); it != commandMap.end(); it++)
		delete it->second;
}

Resource::Resource(const Resource& rhs) {(void)rhs;}

Resource&	Resource::operator=(const Resource& rhs) {(void)rhs; return *this;}

Client*	Resource::findClient(const std::string& name) {
	for (std::map<int, Client>::iterator it = clientMap.begin(); it != clientMap.end(); it++) {
		if (name == it->second.getNickname())
			return &(it->second);
	}
	return NULL;
}

Client*	Resource::findClient(const int& fd) {
	std::map<int, Client>::iterator it = clientMap.find(fd);
	if (it != clientMap.end())
		return &(it->second);
	return NULL;
}

Channel*	Resource::findChannel(const std::string& name) {
	std::map<std::string, Channel>::iterator it = channelMap.find(name);
	if (it != channelMap.end())
		return &(it->second);
	return NULL;
}

Command*	Resource::findCommand(const std::string& prefix) {
	std::map<std::string, Command*>::iterator it = commandMap.find(prefix);
	if (it != commandMap.end())
		return it->second;
	return NULL;
}

void	Resource::addClient(const int& fd) {
	Client newClient(fd);

	clientMap.insert(std::make_pair(fd, newClient));
}

void	Resource::addChannel(const std::string& name) {
	Channel newChannel(name);

	channelMap.insert(std::make_pair(name, newChannel));
}

void	Resource::removeClient(const int& fd) {clientMap.erase(fd);}

void	Resource::removeChannel(const std::string& name) {channelMap.erase(name);}

int		Resource::getClientCount() {return clientMap.size();}

const std::string& Resource::getPassword() const {return password;}

void	Resource::removeClientFromChannel(Client* client) {
	for (std::map<std::string, Channel>::iterator it = channelMap.begin(); it != channelMap.end(); it++)
	{
		it->second.removeClient(client);
		it->second.removeOperator(client);
	}
}