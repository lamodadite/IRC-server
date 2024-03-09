#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Privmsg : public Command {
	public:
		Privmsg();
		Privmsg(const Privmsg& rhs);
		Privmsg& operator=(const Privmsg& rhs);
		~Privmsg();

		void	execute(Resource& resource, Message message);

	private:
		void	splitByComma(std::vector<std::string>& target, std::string param);
		void	SendMessageToClient(Client* client, const std::string &target, const std::string comment);

};

#endif