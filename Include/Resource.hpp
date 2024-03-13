#ifndef RESOURCE_HPP
#define RESOURCE_HPP

# include "Irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include "Commands.hpp"

class Channel;
class Client;

class Resource {
	public:
		Resource();
		~Resource();

		Client*	findClient(const std::string& name);
		Client*	findClient(const int& fd);
		Channel*	findChannel(const std::string& name);
		Command*	findCommand(const std::string& prefix);
		
		void	setPassword(const std::string& password);
		void	addClient(const int& fd);
		void	addChannel(const std::string& name);
		void	removeClient(const int& fd);
		void	removeChannel(const std::string& name);
		int		getClientCount();

		const std::string& getPassword() const;

		void	removeEmptyChannel();

	private:
		Resource(const Resource& rhs);
		Resource& operator=(const Resource& rhs);
		
		std::map<std::string, Channel>	channelMap;
		std::map<int, Client>			clientMap;
		std::map<std::string, Command*>	commandMap;
		std::string	password;
};

#endif