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

		void	handleMessage(std::vector<Message>& messages, const int& fd, std::string buffer);

	private:
		void	splitBuffer(std::vector<std::string>& splitedBuffer, std::string& buffer);
		void	splitToParam(std::string& splitedBuffer, Message& message);
		bool	isCommand(const std::string& param);
};

#endif