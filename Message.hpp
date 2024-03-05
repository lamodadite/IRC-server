#ifndef MESSAGE_HPP
#define MESSAGE_HPP

# include "Irc.hpp"

class Message {
	public:
		Message();
		Message(const Message& rhs);
		Message& operator=(const Message& rhs);
		~Message();

		const std::string&	getFirstParam();
	private:
		std::vector<std::string>	param;
		std::string					firstParam;

		bool	isCommand;
		int 	clientFd;
};

#endif