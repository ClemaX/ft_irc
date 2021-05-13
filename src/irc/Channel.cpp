#include <irc/Channel.hpp>
#include <irc/Server.hpp>

namespace irc
{

// ======== ChannelClient ========
















// ======== Channel ========

	Channel::Channel(std::string const& channelName)
	throw(InvalidChannelNameException)
	: name(setChannelName(channelName))
	{
		if (checkChannelName(name) == false)
			throw InvalidChannelNameException();
		else if (isNetworkUnmoderatedChannel())
			channelModes.binMode = (M_n | M_t);
	}


	Channel const&
	Channel::operator<<(NumericReply const& reply)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*it->first << reply;
		return (*this);
	}

	Channel const&
	Channel::operator<<(PrivateMessage const& reply)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*it->first << reply;
		return (*this);
	}

	std::string
	Channel::setChannelName(const std::string& channelName)
	{
		if (!isNetworkSafeChannel())
			return (ft::strToLower(channelName));

		std::string str = ft::strToLower(channelName);
		channelType = str.at(0);

		std::string prefix;
		srand (time(NULL));
		static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz0123456789";
		for (size_t i = 0 ; i < 5UL ; i++)
			prefix.push_back(alphanum[rand() % ARRAY_SIZE(alphanum)]);
		str.insert(1, prefix);
		return (str);
	}

// Get functions


	Client*
	Channel::getUser(std::string const& clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin()
		; it != clientsMap.end(); it++)
			if (it->first->nickname == clientNickname)
				return (it->first);
		return (NULL);
	}


// Set functions



// Check functions
	bool
	Channel::checkChannelName(const std::string& str) const
	{
		if (str.length() < 2 || str.length() > 50)
			return (false);
		if (str.at(0) != '&' && str.at(0) != '#' && str.at(0) != '+' && str.at(0) != '!')
			return (false);
		if (str.find(' ') != std::string::npos || str.find(',') != std::string::npos || str.find('\'') != std::string::npos)
			return (false);
		return (true);
	}

	bool
	Channel::isInChannel(std::string const& clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
			if (it->first->nickname == clientNickname)
				return (true);
		return (false);
	}



	bool
	Channel::isOperator(Client* const client) const
	{ return (check_user_mod(channelModes.modesMap, client->nickname, M_O | M_o)); }

	bool
	Channel::isCreator(Client* const client) const
	{ return (check_user_mod(channelModes.modesMap, client->nickname, M_O)); }


	bool
	Channel::isStatusVoice(Client* const user) const
	{ return (check_user_mod(channelModes.modesMap, user->nickname, M_v)); }

	bool
	Channel::isStatusBanned(Client* const user) const
	{ return (check_user_mod(channelModes.modesMap, user->nickname, M_b)); }

	bool
	Channel::isStatusException(Client* const user) const
	{ return (check_user_mod(channelModes.modesMap, user->nickname, M_e)); }

	bool
	Channel::isStatusInvite(Client* const user) const
	{ return (check_user_mod(channelModes.modesMap, user->nickname, M_i)); }



	bool
	Channel::isLocalChannelVisibleForClient(Client const *client) const
	{ return (!isLocalChannel() || (!serversMap.empty() && serversMap.begin()->first == client->server)); }


// Message

	void
	Channel::receiveMessage(Client *const client, std::string const& message)
	{
		if ((!isInChannel(client) && channelModes.binMode & M_n)
		|| (channelModes.binMode & M_m && !isStatusVoice(client) && !isOperator(client))
		|| (isStatusBanned(client)))
			*client << CannotSendToChanError(gHostname, name);
		else
			*this << PrivateMessage(client->nickname, message);
	}

	void
	Channel::receiveNotice(Client* const client, std::string const& message)
	{
		if (!((!isInChannel(client) && channelModes.binMode & M_n)
		|| (channelModes.binMode & M_m && !isStatusVoice(client) && !isOperator(client))
		|| (isStatusBanned(client))))
			*this << PrivateMessage(client->nickname, message);
	}


// Add/Remove functions
	bool	Channel::addClient(Client* const client, std::string& password, bool isChannelOperator)
	{
		if (clientsMap.find(client) != clientsMap.end())
			return false;
		if (channelModes.l > 0 && clientsMap.size() >= channelModes.l)
		{
			*client << ChannelIsFullError(gHostname, name);
			return false;
		}
		if (isStatusBanned(client) && !isStatusException(client))
		{
			*client << BannedFromChanError(gHostname, name);
			return false;
		}
		if ((channelModes.binMode & M_i) && !isStatusInvite(client))
		{
			*client << InviteOnlyChanError(gHostname, name);
			return false;
		}
		if (channelModes.k.compare("") && channelModes.k == password)
		{
			*client << BadChannelKeyError(gHostname, name);
			return false;
		}
		clientsMap[client] = ChannelClient(client, isChannelOperator);
		if (isNetworkSafeChannel() && !clientsMap.size())
			addCreator(client->nickname);
		else if (isChannelOperator)
			addOperator(client->nickname);
		client->joinChannel(this);
		*this << JoinChannelMessage(client->nickname, name);
		*client << TopicReply(gHostname, name, topic);
		*client << ChannelNamesReply(gHostname, this);

		return true;
	}

	bool
	Channel::addServer(Server* const server)
	{
		const Channel::channelServerMap::iterator& it = serversMap.find(server);
		if (it != serversMap.end())
			return (false);
		it->second = server;
		return (true);
	}

	bool
	Channel::removeClient(Client* const client, std::string const& leaveMessage)
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

	bool
	Channel::close()
	{
		if (serversMap.empty() == false)
			serversMap.begin()->second->database.dataChannelsMap.erase(name);
		delete this;
		return (true);
	}







	namespace
	{
		template <class __Reply, class __Channel>
		inline bool
		user_in_channel(const std::string& nickname, __Channel* const c)
		{
			if (!c->isInChannel(nickname))
			{
				__Reply(gHostname, nickname, c->name);
				return (false);
			}
			return (true);
		}

		template <class __Reply, class Map, class __Channel>
		bool
		add_mode(Map& m, __Channel* const c, const std::string& key, size_t mask,
		const char*const mode_msg)
		{
			const typename Map::iterator& it = m.find(key);
			if (it != m.end())
			{
				it->second |= mask;
				*c << __Reply(gHostname, c->name, mode_msg, key);
				return (true);
			}
			return (false);
		}

		template <class __Reply, class Map, class __Channel>
		bool
		reset_mode(Map& m, __Channel* const c, const std::string& key, size_t mask,
		const char*const mode_msg)
		{
			const typename Map::iterator& it = m.find(key);
			if (it != m.end())
			{
				it->second &= ~mask;
				*c << __Reply(gHostname, c->name, mode_msg, key);
				return (true);
			}
			return (false);
		}
	}

	bool
	Channel::addCreator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.modesMap, this, nickname, M_O, "+O"));
	}

	bool
	Channel::removeCreator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.modesMap, this, nickname, M_O, "-O"));
	}

	bool
	Channel::addOperator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.modesMap, this, nickname, M_o, "+o"));
	}

	bool
	Channel::removeOperator(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.modesMap, this, nickname, M_o, "-o"));
	}

	bool
	Channel::addVoice(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& add_mode<ChannelModeIsReply>(channelModes.modesMap, this, nickname, M_v, "+v"));
	}

	bool
	Channel::removeVoice(const std::string& nickname)
	{
		return (user_in_channel<UserNotInChannelError>(nickname, this)
		&& reset_mode<ChannelModeIsReply>(channelModes.modesMap, this, nickname, M_v, "-v"));
	}

	bool
	Channel::addBanned(const std::string& nickname)
	{
		// NOTE: Does not check if is in channel
		return (add_mode<BanListReply>(channelModes.modesMap, this, nickname, M_b, "+"));
	}

	bool
	Channel::removeBanned(const std::string& nickname)
	{
		// NOTE: Does not check if is in channel
		return (reset_mode<BanListReply>(channelModes.modesMap, this, nickname, M_b, "-"));
	}

	bool
	Channel::addException(const std::string& nickname)
	{
		// NOTE: Does not check if is in channel
		return (add_mode<ExceptionListReply>(channelModes.modesMap, this, nickname, M_e, "+"));
	}

	bool
	Channel::removeException(const std::string& nickname)
	{
		// NOTE: Does not check if is in channel
		return (reset_mode<ExceptionListReply>(channelModes.modesMap, this, nickname, M_e, "-"));
	}

	bool
	Channel::addInviteList(const std::string& nickname)
	{
		// NOTE: Does not check if is in channel
		return (add_mode<InviteListReply>(channelModes.modesMap, this, nickname, M_I, "+"));
	}

	bool
	Channel::removeInviteList(const std::string& nickname)
	{
		// NOTE: Does not check if is in channel
		return (reset_mode<InviteListReply>(channelModes.modesMap, this, nickname, M_I, "-"));
	}
}
