#ifndef INVITE_HPP
#define INVITE_HPP

# include "Irc.hpp"
# include "Command.hpp"

class Invite : public Command {
	public:
		Invite();
		Invite(const Invite& rhs);
		Invite& operator=(const Invite& rhs);
		~Invite();

		void execute(Resource& resource, Message message);

	private:
};

#endif