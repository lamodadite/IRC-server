#ifndef TOPIC_HPP
#define TOPIC_HPP

# include "Irc.hpp"
# include "Command.hpp"
# include "Resource.hpp"

class Resource;

class Topic : public Command {
	public:
		Topic();
		Topic(const Topic& rhs);
		Topic& operator=(const Topic& rhs);
		~Topic();

		void execute(Resource& resource, Message message);
	private:
		void	sendMessageToChannel(Channel* channel, std::string message);
};

#endif