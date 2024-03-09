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
		Mode& operator=(const Mode& rhs);
		~Mode();

		void execute(Resource& resource, Message message);

	private:
		void parseModeString(Channel& channel, Message &message);
};

#endif