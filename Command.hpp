#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Irc.hpp"
#include "Message.hpp"
#include "Resource.hpp"

class Command {
	private:
	public:
		Command();
		Command(const Command& rhs);
		Command& operator=(const Command& rhs);
		virtual ~Command();
		virtual void execute(Resource& resource, Message message) = 0;
};

#endif