#ifndef KICK_HPP
#define KICK_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Kick : public Command {
	public:
		Kick();
		Kick(const Kick& rhs);
		Kick& operator=(const Kick& rhs);
		~Kick();

		void execute(Resource& resource, Message message);

	private:
		void	SendMessageToClient(Client* client, Channel *channel, Client *kickedClient);
};

#endif