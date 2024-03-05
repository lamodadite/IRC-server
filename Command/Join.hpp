#ifndef JOIN_HPP
#define JOIN_HPP

# include "Irc.hpp"

class Join : public Command {
	private:

	public:
		Join();
		Join(const Join& rhs);
		Join& operator=(const Join& rhs);
		~Join();

		void execute(Resource& resource, Message message);
};

#endif