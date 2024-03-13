#ifndef REPLY_HPP
#define REPLY_HPP

# include "Irc.hpp"
//# include "Resource.hpp"

class Client;
class Command;
class Channel;

class Reply	{
	public:
		Reply();
		Reply(const Reply& rhs);
		Reply& operator=(const Reply& rhs);
		~Reply();

		void	errNeedMoreParams(Client* client, const std::string& command);
		void	errAlreadyRegistered(Client* client);
		void	errPasswdMisMatch(Client* client);
		void	errNoNicknameGiven(Client* client);
		void	errErroneusNickname(Client* client);
		void	errNicknameInUse(Client* client);
		void	errNoSuchChannel(Client* client, std::string channel);
		void	errTooManyChannel(Client* client, Channel* channel);
		void	errBadChannelKey(Client* client, Channel* channel);
		void	errChannelIsFull(Client* client, Channel* channel);
		void	errInviteOnlyChan(Client* client, Channel* channel);
		void	errBadChanMask(Client* client);
		void	rplTopic(Client* client, Channel* channel);
		void	rplTopicWhoTime(Client* client, Channel* channel);
		void	errNotOnChannel(Client* client, Channel* channel);
		void	errChanOperIvsNeeded(Client* client, Channel* channel);
		void	rplNoTopic(Client* client, Channel* channel);
		void	rplInviting(Client* client, std::string nick, Channel* channel);
		void	errUserOnChannel(Client* client, std::string nick, Channel* channel);
		void	errUserNotInChannel(Client* client, std::string nick, Channel* channel);
		void	rplChannelModeIs(Client* client, Channel* channel);
		void	rplCreationTime(Client* client, Channel* channel);
		void	errNoSuchNick(Client* client, std::string nickname);
		void	errCannotSendToChan(Client* client, Channel* channel);
		void	errNoRecipient(Client* client, const std::string& command);
		void	errNoTextToSend(Client* client);
		void	errUnknownCommand(Client* client, const std::string& message);
};

#endif