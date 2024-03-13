#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include "Irc.hpp"
# include "Client.hpp"

class Channel {
	public:
		Channel(const std::string& name);
		Channel(const Channel& rhs);
		~Channel();

		bool	hasClient(Client* client) const;
		bool	hasOperator(Client* client) const;

		void	addClient(Client *client);
		void	addOperator(Client *client);

		void	removeClient(Client *client);
		void	removeOperator(Client *client);
		void	removeInvited(Client *client);

		const std::string&	getName() const;
		const std::string&	getTopic() const;
		const std::string&	getMode() const;
		const std::string&	getKey() const;
		const std::set<Client*>&	getClientList() const;
		const size_t&	getUserLimit() const;
		const std::string&	getCreationTime() const;
		const std::string&	getTopicAuthor() const;
		const std::string&	getTopicSetTime() const;

		void	setName(const std::string& name);
		void	setTopic(const std::string& topic);
		void	setKey(const std::string& key);
		void	setUserLimit(const size_t& userLimit);
		void	setCreationTime(const std::string& creationTime);
		void	setTopicAuthor(const std::string& topicAuthor);
		void	setTopicSetTime(const std::string& topicSetTime);

		void	addMode(const char mode);
		void	removeMode(const char mode);

		void	removeKey();
		void	inviteClient(Client* client);
		bool	hasMode(const char mode) const;
		bool	checkInvited(Client* client) const;

		void	clearInvitedList();

	private:
		Channel();
		Channel&	operator=(const Channel& rhs);

		std::set<Client*>	clientList;
		std::set<Client*>	operatorList;
		std::set<Client*>	invitedList;

		std::string			key;
		std::string			name;
		std::string			topic;
		std::string			mode;
		size_t				userLimit;
		std::string			creationTime;
		std::string			topicAuthor;
		std::string			topicSetTime;
};

#endif