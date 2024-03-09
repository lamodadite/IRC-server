#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Reply.hpp"
#include "Irc.hpp"
#include "Message.hpp"

class Resource;
class Reply;

class Command {
	public:
		Command();
		Command(const Command& rhs);
		Command& operator=(const Command& rhs);
		virtual ~Command();
		virtual void execute(Resource& resource, Message message) = 0;
		
	protected:
		Reply reply;
};

#endif