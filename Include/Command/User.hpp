#ifndef USER_HPP
#define USER_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class User : public Command {
	public:
		User();
		User(const User& rhs);
		User& operator=(const User& rhs);
		~User();
		void	execute(Resource& resource, Message message);

	private:
};

#endif