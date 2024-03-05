#ifndef TOPIC_HPP
#define TOPIC_HPP

# include "Irc.hpp"

class Topic : public Command {
	private:

	public:
		Topic();
		Topic(const Topic& rhs);
		Topic& operator=(const Topic& rhs);
		~Topic();

		void execute(Resource& resource, Message message);
};

#endif