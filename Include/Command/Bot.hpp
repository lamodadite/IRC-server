#ifndef BOT_HPP
#define BOT_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Bot : public Command {
	public:
		Bot();
		Bot(const Bot& rhs);
		Bot& operator=(const Bot& rhs);
		~Bot();

		void execute(Resource& resource, Message message);

	private:
		int	checkArgument(Message message);
		void	whatsArgument(Client* client);
};

#endif