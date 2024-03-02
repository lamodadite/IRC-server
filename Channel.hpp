#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "Irc.hpp"
# include "Client.hpp"

class Channel {
	public:
		Channel(std::string channel_name);
		~CLient();

	private:
		Channel();
		Channel(const Channel& rhs);
		Channel& operator=(const Channel& rhs);

		std::map<std::string, Client> _client_list;
		std::vector<std::string>			_kicked_client;

		std::string _name;
		std::string	_topic;
		std::string _mode;
};

#endif