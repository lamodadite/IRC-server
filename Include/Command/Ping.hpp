#ifndef PONG_HPP
#define PONG_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Ping : public Command {
	public:
		Ping();
		Ping(const Ping& rhs);
		Ping& operator=(const Ping& rhs);
		~Ping();
		void	execute(Resource& resource, Message message);

	private:
		void	SendMessageToClient(Client* target);
};

#endif