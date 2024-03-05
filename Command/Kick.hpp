#ifndef KICK_HPP
#define KICK_HPP

# include "Irc.hpp"

class Kick : public Command {
	private:

	public:
		Kick();
		Kick(const Kick& rhs);
		Kick& operator=(const Kick& rhs);
		~Kick();

		void execute(Resource& resource, Message message);
};

#endif