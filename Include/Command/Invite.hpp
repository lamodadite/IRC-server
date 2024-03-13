#ifndef INVITE_HPP
#define INVITE_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Invite : public Command {
	public:
		Invite();
		Invite(const Invite& rhs);
		Invite& operator=(const Invite& rhs);
		~Invite();

		void execute(Resource& resource, Message message);

	private:
		void sendMessageToChannel(Client* client, Client* invitedClient, Channel* channel);
};

#endif