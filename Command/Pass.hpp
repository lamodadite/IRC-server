#ifndef PASS_HPP
#define PASS_HPP

# include "Irc.hpp"

class Pass : public Command {
	private:

	public:
		Pass();
		Pass(const Pass& rhs);
		Pass& operator=(const Pass& rhs);
		~Pass();

		void execute(Resource& resource, Message message);
};

#endif