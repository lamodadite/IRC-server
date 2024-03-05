#include "Resource.hpp"

Resource::Resource() {}
Resource::~Resource() {}
Resource::Resource(const Resource& rhs) {(void)rhs;}
Resource& Resource::operator=(const Resource& rhs) {(void)rhs; return *this;}

Client& Resource::findClient(const std::string& name) {
	for (std::map<int, Client>::iterator it = clientMap.begin(); it != clientMap.end(); it++) {
		if (name == it->second.getNickname())
			return it->second;
	}
	throw std::exception();
}

Client& Resource::findClient(const int& fd) {
	std::map<int, Client>::iterator it = clientMap.find(fd);
	if (it == clientMap.end())
		throw std::exception();
	return it->second;
}

Channel& Resource::findChannel(const std::string& name) {
	std::map<std::string, Channel>::iterator it = channelMap.find(name);
	if (it == channelMap.end())
		throw std::exception();
	return it->second;	
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