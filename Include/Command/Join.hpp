#ifndef JOIN_HPP
#define JOIN_HPP

# include "Irc.hpp"
# include "Command.hpp"

class Join : public Command {
	public:
		Join();
		Join(const Join& rhs);
		Join& operator=(const Join& rhs);
		~Join();

		void	execute(Resource& resource, Message message);

	private:
		void	sendMessageToChannel(Channel* channel, std::string message);
		void	splitByComma(std::vector<std::string>& target, std::string param);
		bool	hasControlG(std::string param);
};	

#endif