#ifndef USER_HPP
#define USER_HPP

# include "Irc.hpp"

class User : public Command {
	private:

	public:
		User();
		User(const User& rhs);
		User& operator=(const User& rhs);
		~User();

		void execute(Resource& resource, Message message);
};

#endif