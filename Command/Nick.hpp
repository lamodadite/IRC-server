#ifndef NICK_HPP
#define NICK_HPP

# include "Irc.hpp"

class Nick : public Command {
	private:

	public:
		Nick();
		Nick(const Nick& rhs);
		Nick& operator=(const Nick& rhs);
		~Nick();

		void execute(Resource& resource, Message message);
};

#endif