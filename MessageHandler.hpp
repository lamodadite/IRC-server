#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

# include "Irc.hpp"
# include "Message.hpp"

class Message;

class MessageHandler {
	public:
		MessageHandler();
		MessageHandler(const MessageHandler& rhs);
		MessageHandler& operator=(const MessageHandler& rhs);
		~MessageHandler();

		std::vector<Message> handleMessage(const int& fd, std::string buffer);
	private:
};

#endif