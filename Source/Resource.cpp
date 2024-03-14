#include "Commands.hpp"
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
	commandMap.insert(std::make_pair("PING", new Ping()));
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
	std::stringstream ss;
	ss << time(NULL);
	newChannel.setCreationTime(ss.str());

	channelMap.insert(std::make_pair(name, newChannel));
}

void	Resource::removeClient(const int& fd) {
	std::map<int, Client>::iterator it = clientMap.find(fd);
	if (it != clientMap.end())
		clientMap.erase(it);
}

void	Resource::removeChannel(const std::string& name) {
	std::map<std::string, Channel>::iterator it = channelMap.find(name);
	if (it != channelMap.end())
		channelMap.erase(it);
}

int		Resource::getClientCount() const {return clientMap.size();}

const std::string& Resource::getPassword() const {return password;}

void	Resource::setPassword(const std::string& password) {this->password = password;}

void	Resource::removeEmptyChannel() {
	std::map<std::string, Channel>::iterator it;
	std::vector<std::map<std::string, Channel>::iterator> emptyChannel;

	for (it = channelMap.begin(); it != channelMap.end(); it++) {
		if (it->second.getClientList().size() == 0)
		{
			it->second.clearInvitedList();
			emptyChannel.push_back(it);
		}
	}
	for (size_t i = 0; i < emptyChannel.size(); i++)
		channelMap.erase(emptyChannel[i]);
}