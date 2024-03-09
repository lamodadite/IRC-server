#ifndef PASS_HPP
#define PASS_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Pass : public Command {
	public:
		Pass();
		Pass(const Pass& rhs);
		Pass& operator=(const Pass& rhs);
		~Pass();

		void execute(Resource& resource, Message message);

	private:
};

#endif