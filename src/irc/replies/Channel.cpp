#include <irc/Channel.hpp>

#include <irc/AClient.hpp>

#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>

namespace irc
{

	Channel const&
	Channel::
	operator<<(IReply const& message)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*it->first << message;
		return (*this);
	}

	AClient*
	Channel::
	getUser(std::string const& clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin()
		; it != clientsMap.end(); it++)
			if (it->first->nickname == clientNickname)
				return (it->first);
		return (NULL);
	}

	bool
	Channel::
	isInChannel(std::string const& clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
			if (it->first->nickname == clientNickname)
				return (true);
		return (false);
	}

	void
	Channel::
	receiveMessage(AClient *const client, std::string const& message)
	{
		if ((!isInChannel(client) && channelModes & Channel::n)
		|| (channelModes & Channel::m && !isStatusVoice(client) && !isOperator(client))
		|| (isStatusBanned(client)))
			*client << CannotSendToChanError(gHostname, name);
		else
			*this << PrivateMessage(client->nickname, message);
	}

	void
	Channel::
	receiveNotice(AClient*const client, std::string const& message)
	{
		if (!((!isInChannel(client) && channelModes & Channel::n)
		|| (channelModes & Channel::m && !isStatusVoice(client) && !isOperator(client))
		|| (isStatusBanned(client))))
			*this << PrivateMessage(client->nickname, message);
	}

	///////////////
	// Modifiers //
	///////////////

	bool
	Channel::addClient(AClient*const client, std::string& password, bool isChannelOperator)
	{
		if (clientsMap.find(client) != clientsMap.end())
			return (false);
		if (channelModes.l > 0 && clientsMap.size() >= channelModes.l)
		{
			*client << ChannelIsFullError(gHostname, name);
			return (false);
		}
		if (isStatusBanned(client) && !isStatusException(client))
		{
			*client << BannedFromChanError(gHostname, name);
			return (false);
		}
		if ((channelModes & Channel::i) && !isStatusInvite(client))
		{
			*client << InviteOnlyChanError(gHostname, name);
			return (false);
		}
		if (channelModes.k.compare("") && channelModes.k == password)
		{
			*client << BadChannelKeyError(gHostname, name);
			return (false);
		}
		clientsMap[client] = ChannelClient(client, isChannelOperator); // NEED THIS ?!?!
		channelModes.channelModes.insert(std::pair<std::string, uint32_t>(client->nickname, 0));
		if (isNetworkSafeChannel() && clientsMap.size() == 1UL) // [WARNING!] THIS LINE WAS EDDITED
			addCreator(client->nickname);
		else if (isChannelOperator)
			addOperator(client->nickname);
		client->joinChannel(this);
		*this << JoinChannelMessage(client->nickname, name);
		*client << TopicReply(gHostname, name, topic);
		*client << ChannelNamesReply(gHostname, this);

		return true;
	}

/* 	bool
	Channel::addServer(__Server* const server)
	{
		const Channel::channelServerMap::iterator& it = serversMap.find(server);
		if (it != serversMap.end())
			return (false);
		serversMap[server] = server;
		return (true);
	} */

	bool
	Channel::
	removeClient(AClient* const client, std::string const& leaveMessage)
	{
		const Channel::channelClientMap::iterator& it = clientsMap.find(client);
		if (it == clientsMap.end())
			return (false);
		*this << LeaveChannelMessage(client->nickname, name, leaveMessage);
		client->leaveChannel(this);
		clientsMap.erase(it);
		if (clientsMap.empty())
			return (close());
		return (true);
	}

}
