#ifndef MODE_HPP
#define MODE_HPP

# include "Irc.hpp"

class Mode : public Command {
	private:

	public:
		Mode();
		Mode(const Mode& rhs);
		Mode& operator=(const Mode& rhs);
		~Mode();

		void execute(Resource& resource, Message message);
};

#endif