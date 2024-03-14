#ifndef MODE_HPP
#define MODE_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Mode : public Command {
	public:
		Mode();
		Mode(const Mode& rhs);
		Mode&	operator=(const Mode& rhs);
		~Mode();

		void	execute(Resource& resource, Message message);

	private:
		void	parseModeString(Channel& channel, Message &message);
		void	sendMessageToChannel(Channel* channel, std::string& replyMessage);

		int		changeModeL(Channel* channel, bool flag, int& index, Message message);
		bool	changeModeI(Channel* channel, bool flag);
		bool	changeModeT(Channel* channel, bool flag);
		bool	changeModeK(Channel* channel, bool flag, int& index, Message message);
		bool	changeModeO(Channel* channel, Resource& resource, bool flag, int& index, Message message);

		const std::string	deleteFailedMode(std::string& modestring);
};

#endif