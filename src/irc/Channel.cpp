#include <irc/Channel.hpp>
#include <irc/Server.hpp>

namespace irc
{

// ======== ChannelClient ========
	ChannelClient::ChannelClient()
		:	client(NULL)
	{ }

	ChannelClient::ChannelClient(Client* client, bool isOp)
		:	client(client)
	{ (void)isOp;}

	ChannelClient::ChannelClient(Client* client)
		:	client(client)
	{ }

	ChannelClient::ChannelClient(const ChannelClient & src)
	{*this = src;}

	ChannelClient::~ChannelClient() {}

	ChannelClient & ChannelClient::operator=(const ChannelClient & src)
	{
		client = src.client;
		return *this;
	}


// ======== ChannelModes ========
	ChannelModes::ChannelModes()
	{ }

	ChannelModes::~ChannelModes() {}


// ======== Channel ========
	Channel::Channel(std::string const& channelName) throw(InvalidChannelNameException)
		:	clientsMap(), serversMap(), topic(""), channelModes(), name(setChannelName(channelName))
	{
		if (checkChannelName(name) == false)
			throw InvalidChannelNameException();
		if (isNetworkUnmoderatedChannel())
			channelModes.binMode = (M_n | M_t);
	}

	Channel::~Channel() {}

	Channel const&	Channel::operator<<(NumericReply const& reply)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*(it->first) << reply;
		return *this;
	}

	Channel const&	Channel::operator<<(PrivateMessage const& reply)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*(it->first) << reply;
		return *this;
	}

	std::string	Channel::setChannelName(std::string channelName)
	{
		std::string str = ft::strToLower(channelName);
		channelType = str[0];

		if (!isNetworkSafeChannel())
			return str;

		std::string prefix = "";
		srand (time(NULL));
		char c;
		static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz0123456789";
		for (int i = 0 ; i < 5 ; i++)
		{
			c = alphanum[rand() % ARRAY_SIZE(alphanum)];
			prefix.push_back(c);
		}
		str.insert(1, prefix);
		return str;
	}

// Get functions
	std::string	Channel::getTopic() const
	{return topic;}

	Client* Channel::getUser(std::string const & clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
		{
			if (it->first->nickname == clientNickname)
				return it->first;
		}
		return NULL;
	}


// Set functions
	void	Channel::setTopic(const std::string & str)
	{topic = str;}


// Check functions
	bool	Channel::checkChannelName(const std::string &str) const
	{
		if (str.length() < 2 || str.length() > 50)
			return false;
		if (str[0] != '&' && str[0] != '#' && str[0] != '+' && str[0] != '!')
			return false;
		if (str.find(' ') != std::string::npos || str.find(',') != std::string::npos || str.find('\'') != std::string::npos)
			return false;
		return true;
	}

	bool	Channel::isInChannel(Client* const client) const
	{return (clientsMap.find(client) != clientsMap.end());}

	bool	Channel::isInChannel(std::string const & clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
		{
			if (it->first->nickname == clientNickname)
				return true;
		}
		return false;
	}

	bool	Channel::isVisibleForClient(Client* const client) const
	{
		return (isInChannel(client) ||
				(!(channelModes.binMode & M_p)  && !(channelModes.binMode & M_s) &&
				isLocalChannelVisibleForClient(client)));
	}

	namespace
	{
		template <class Map>
		inline bool
		check_user_mod(const Map& m, const std::string& key, size_t mode_mask)
		{
			const typename Map::const_iterator& it = m.find(key);
			return (it != m.end() && (it->second & mode_mask));
		}
	}

	bool
	Channel::isOperator(Client* const client) const
	{ return (check_user_mod(channelModes.modesMap, client->nickname, M_O | M_o)); }

	bool
	Channel::isOperator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.modesMap, clientNickname, M_O | M_o)); }

	bool
	Channel::isCreator(Client* const client) const
	{ return (check_user_mod(channelModes.modesMap, client->nickname, M_O)); }

	bool
	Channel::isCreator(const std::string& clientNickname) const
	{ return (check_user_mod(channelModes.modesMap, clientNickname, M_O)); }

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
	Channel::isLocalChannel(void) const
	{ return channelType == '&'; }

	bool
	Channel::isNetworkChannel(void) const
	{ return channelType == '#'; }

	bool
	Channel::isNetworkSafeChannel(void) const
	{ return channelType == '!'; }

	bool
	Channel::isNetworkUnmoderatedChannel(void) const
	{ return channelType == '+'; }

	bool
	Channel::isLocalChannelVisibleForClient(Client const *client) const
	{ return (!isLocalChannel() || (!serversMap.empty() && serversMap.begin()->first == client->server)); }


// Message

	void	Channel::receiveMessage(Client *client, std::string const &message)
	{
		if (!isInChannel(client) && (channelModes.binMode & M_n))
			*client << CannotSendToChanError(gHostname, name);
		else if ((channelModes.binMode & M_m) && (!isStatusVoice(client) && !isOperator(client)))
			*client << CannotSendToChanError(gHostname, name);
		else if (isStatusBanned(client))
			*client << CannotSendToChanError(gHostname, name);
		else
			*this << PrivateMessage(client->nickname, message);
	}

	void	Channel::receiveNotice(Client *client, std::string const &message)
	{
		if (!isInChannel(client) && (channelModes.binMode & M_n))
			return ;
		else if ((channelModes.binMode & M_m) && (!isStatusVoice(client) && !isOperator(client)))
			return ;
		else if (isStatusBanned(client))
			return ;
		else
			*this << PrivateMessage(client->nickname, message);
	}


// Add/Remove functions
	bool	Channel::addClient(Client* client, std::string & password, bool	isChannelOperator)
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

	bool	Channel::addServer(Server* server)
	{
		if (serversMap.find(server) != serversMap.end())
			return false;
		serversMap[server] = server;

// std::cout << name << ": new server added\n";

		return true;
	}

	bool	Channel::removeClient(Client* client, std::string const &leaveMessage)
	{
		if (clientsMap.find(client) == clientsMap.end())
			return false;
		*this << LeaveChannelMessage(client->nickname, name, leaveMessage);
		client->leaveChannel(this);
		clientsMap.erase(client);
		if (clientsMap.empty())
			return close();
		return true;
	}

	bool	Channel::close()
	{
		if (!serversMap.empty())
			serversMap.begin()->second->database.dataChannelsMap.erase(name);
		delete this;

// std::cout << "channel " << name << " has been closed\n";

		return true;
	}







	/////////////////
	// Handle mods //
	/////////////////

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
