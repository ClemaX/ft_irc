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
		:	O(), o(), v(), binMode(0), l(0), k(""), b(), e(), I()
	{ }

	ChannelModes::~ChannelModes() {}


// ======== Channel ========
	Channel::Channel(std::string const& channelName) throw(InvalidChannelNameException)
		:	clientsMap(), serversMap(), topic(""), channelModes(), name(setChannelName(channelName))
	{
		if (checkChannelName(name) == false)
			throw InvalidChannelNameException();
		if (isNetworkUnmoderatedChannel())
			channelModes.binMode |= (M_n | M_t);
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
		char alphanum[37] = "abcdefghijklmnopqrstuvwxyz0123456789";
		for (int i = 0 ; i < 5 ; i++)
		{
			c = alphanum[rand() % 37];
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

	bool	Channel::isInChannel(Client *client) const
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

	bool	Channel::isVisibleForClient(Client *client) const
	{
		return (isInChannel(client) ||
				(!(channelModes.binMode & M_p)  && !(channelModes.binMode & M_s) &&
				isLocalChannelVisibleForClient(client)));
	}

	bool	Channel::isOperator(Client *client) const
	{
		return (channelModes.o.find(client->nickname) != channelModes.o.end() ||
				channelModes.O.find(client->nickname) != channelModes.O.end());
	}

	bool	Channel::isOperator(std::string const & clientNickname) const
	{
		return (channelModes.o.find(clientNickname) != channelModes.o.end() ||
				channelModes.O.find(clientNickname) != channelModes.O.end());
	}

	bool	Channel::isCreator(Client *client) const
	{return (channelModes.O.find(client->nickname) != channelModes.O.end());}

	bool	Channel::isCreator(std::string const & clientNickname) const
	{return (channelModes.O.find(clientNickname) != channelModes.O.end());}

	bool	Channel::isStatusVoice(Client *user) const
	{return (channelModes.v.find(user->nickname) != channelModes.v.end());}

	bool	Channel::isStatusBanned(Client *user) const
	{return (channelModes.b.find(user->nickname) != channelModes.b.end());}

	bool	Channel::isStatusException(Client *user) const
	{return (channelModes.e.find(user->nickname) != channelModes.e.end());}

	bool	Channel::isStatusInvite(Client *user) const
	{return (channelModes.I.find(user->nickname) != channelModes.I.end());}

	bool	Channel::isLocalChannel(void) const
	{return channelType == '&';}
	bool	Channel::isNetworkChannel(void) const
	{return channelType == '#';}
	bool	Channel::isNetworkSafeChannel(void) const
	{return channelType == '!';}
	bool	Channel::isNetworkUnmoderatedChannel(void) const
	{return channelType == '+';}

	bool	Channel::isLocalChannelVisibleForClient(Client const *client) const
	{return (!isLocalChannel() || (serversMap.size() && serversMap.begin()->first == client->server));}


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
		if (channelModes.k.compare("") && channelModes.k.compare(password))
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


// Modes functions

	bool	Channel::addCreator(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(gHostname, nickname, name);
			return false;
		}
		if (channelModes.O.find(nickname) != channelModes.O.end())
			return false;
		channelModes.O[nickname] = nickname;
		*this << ChannelModeIsReply(gHostname, name, "+O", nickname);
		return true;
	}
	bool	Channel::removeCreator(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(gHostname, nickname, name);
			return false;
		}
		if (channelModes.O.find(nickname) == channelModes.O.end())
			return false;
		channelModes.O.erase(nickname);
		*this << ChannelModeIsReply(gHostname, name, "-O", nickname);
		return true;
	}

	bool	Channel::addOperator(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(gHostname, nickname, name);
			return false;
		}
		if (channelModes.o.find(nickname) != channelModes.o.end())
			return false;
		channelModes.o[nickname] = nickname;
		*this << ChannelModeIsReply(gHostname, name, "+o", nickname);
		return true;
	}
	bool	Channel::removeOperator(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.o.find(nickname) == channelModes.o.end())
			return false;
		channelModes.o.erase(nickname);
		*this << ChannelModeIsReply(gHostname, name, "-o", nickname);
		return true;
	}

	bool	Channel::addVoice(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(gHostname, nickname, name);
			return false;
		}
		if (channelModes.v.find(nickname) != channelModes.v.end())
			return false;
		channelModes.v[nickname] = nickname;
		*this << ChannelModeIsReply(gHostname, name, "+v", nickname);
		return true;
	}
	bool	Channel::removeVoice(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.v.find(nickname) == channelModes.v.end())
			return false;
		channelModes.v.erase(nickname);
		*this << ChannelModeIsReply(gHostname, name, "-v", nickname);
		return true;
	}



	bool	Channel::addBanned(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(gHostname, nickname, name);
		// 	return false;
		// }
		if (channelModes.b.find(nickname) != channelModes.b.end())
			return false;
		channelModes.b[nickname] = nickname;
		*this << BanListReply(gHostname, name, "+", nickname);
		return true;
	}
	bool	Channel::removeBanned(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(gHostname, nickname, name);
		// 	return false;
		// }
		if (channelModes.b.find(nickname) == channelModes.b.end())
			return false;
		channelModes.b.erase(nickname);
		*this << BanListReply(gHostname, name, "-", nickname);
		return true;
	}

	bool	Channel::addException(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(gHostname, nickname, name);
		// 	return false;
		// }
		if (channelModes.e.find(nickname) != channelModes.e.end())
			return false;
		channelModes.e[nickname] = nickname;
		*this << ExceptionListReply(gHostname, name, "+", nickname);
		return true;
	}
	bool	Channel::removeException(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(gHostname, nickname, name);
		// 	return false;
		// }
		if (channelModes.e.find(nickname) == channelModes.e.end())
			return false;
		channelModes.e.erase(nickname);
		*this << ExceptionListReply(gHostname, name, "-", nickname);
		return true;
	}

	bool	Channel::addInviteList(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(gHostname, nickname, name);
		// 	return false;
		// }
		if (channelModes.I.find(nickname) != channelModes.I.end())
			return false;
		channelModes.I[nickname] = nickname;
		*this << InviteListReply(gHostname, name, "+", nickname);
		return true;
	}
	bool	Channel::removeInviteList(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(gHostname, nickname, name);
		// 	return false;
		// }
		if (channelModes.I.find(nickname) == channelModes.I.end())
			return false;
		channelModes.I.erase(nickname);
		*this << InviteListReply(gHostname, name, "-", nickname);
		return true;
	}


}
