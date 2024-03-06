#ifndef MESSAGE_HPP
#define MESSAGE_HPP

# include "Irc.hpp"

class Message {
	public:
		Message();
		Message(const Message& rhs);
		Message& operator=(const Message& rhs);
		~Message();

		const std::string&	getFirstParam() const;
		const std::vector<std::string>&	getParam() const;
		const int& getClientFd() const;
		const bool& getIsCommand() const;
		const	std::string&	getOriginalMessage() const;

		void	setClientFd(const int& clientFd);
		void	setIsCommand(const bool& isCommand);
		void	setParam(const std::vector<std::string>& param);
		void	setFirstParam(const std::string& firstParam);
		void	setOriginalMessage(const std::string& message);

	private:
		std::vector<std::string>	param;
		std::string					firstParam;
		std::string					originalMessage;

		bool	isCommand;
		int 	clientFd;
};

#endif