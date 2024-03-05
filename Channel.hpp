#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "Irc.hpp"
# include "Client.hpp"

class Channel {
	public:
		Channel(const std::string& name);
		Channel(const Channel& rhs);
		~Channel();

	private:
		Channel();
		Channel& operator=(const Channel& rhs);

		std::map<std::string, Client>	clientList;
		std::vector<std::string>		kickedClient;

		std::string	name;
		std::string	topic;
		std::string	mode;
};

#endif