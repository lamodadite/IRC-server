#ifndef REPLY_HPP
#define REPLY_HPP

# include "Irc.hpp"
# include "Resource.hpp"

class Reply	{
	public:
		Reply();
		Reply(const Reply& rhs);
		Reply& operator=(const Reply& rhs);
		~Reply();

		void	sendToClient(Client* client, Resource& resource, Message& message);
		void	errNeedMoreParams(Client* client, const std::string& command);
};

#endif