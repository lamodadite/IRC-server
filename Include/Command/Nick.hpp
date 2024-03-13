#ifndef NICK_HPP
#define NICK_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Nick : public Command {
	public:
		Nick();
		Nick(const Nick& rhs);
		Nick&	operator=(const Nick& rhs);
		~Nick();

		void	execute(Resource& resource, Message message);

	private:
		bool	isValidNickname(const std::string& nickname) const;
		void	SendMessageToClient(Client* client);
};

#endif