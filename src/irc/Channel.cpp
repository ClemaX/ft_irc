#include <irc/Channel.hpp>

namespace irc
{

// ======== ChannelClient ========
	ChannelClient::ChannelClient()
		:	client(NULL)
		// :	client(NULL), isChannelOperator(false)
	{ }

	ChannelClient::ChannelClient(Client* client, bool isOp)
		:	client(client)
		// :	client(client), isChannelOperator(isOp)
	{ (void)isOp;}

	ChannelClient::ChannelClient(Client* client)
		:	client(client)
		// :	client(client), isChannelOperator(false)
	{ }

	ChannelClient::ChannelClient(const ChannelClient & src)
	{*this = src;}

	ChannelClient::~ChannelClient() {}

	ChannelClient & ChannelClient::operator=(const ChannelClient & src)
	{
		client = src.client;
		// isChannelOperator = src.isChannelOperator;
		return *this;
	}








// ======== ChannelModes ========
	ChannelModes::ChannelModes()
		:	O(), o(), v(), a(false), i(false), m(false), n(false), q(false),
			p(false), s(false), r(false), t(false), l(0), k(""), b(), e(), I()
	{ }

	ChannelModes::~ChannelModes() {}








// ======== Channel ========
	// Channel::Channel()
	// 	:	clientsMap(), serversMap(), topic(""), channelModes(), name("")
	// { }

	Channel::Channel(std::string const& channelName) throw(InvalidChannelNameException)
		:	clientsMap(), serversMap(), topic(""), channelModes(), name(ft::strToLower(channelName))
	{
		if (checkChannelName(name) == false)
			throw InvalidChannelNameException();
	}

	Channel::~Channel() {}

	Channel const&	Channel::operator<<(NumericReply const& reply)
	{
		for (Channel::channelClientMap::iterator it = clientsMap.begin() ; it != clientsMap.end() ; it++)
			*(it->first) << reply;
		return *this;
	}

// Get functions

	// ChannelModes	Channel::getModes() const
	// {return channelModes;}

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
	bool	Channel::checkChannelName(const std::string &str) const	// still need to add the channel mask part (with ':')
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

	bool	Channel::isVisible(Client *client) const
	{return (isInChannel(client) || (channelModes.p == false && channelModes.s == false));}


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


	bool	Channel::isStatusBanned(Client *user) const
	{return (channelModes.b.find(user->nickname) != channelModes.b.end());}

	bool	Channel::isStatusException(Client *user) const
	{return (channelModes.e.find(user->nickname) != channelModes.e.end());}

	bool	Channel::isStatusInvite(Client *user) const
	{return (channelModes.I.find(user->nickname) != channelModes.I.end());}








// Add/Remove functions
	bool	Channel::addClient(Client* client, std::string & password, bool	isChannelOperator)
	{
		if (clientsMap.find(client) != clientsMap.end())
		{
			// *client << 
			return false;	// is there an error when joining a channel you're already in ?
		}
		if (channelModes.l > 0 && clientsMap.size() >= channelModes.l)
		{
			*client << ChannelIsFullError(SERVER_NAME, name);
			return false;
		}
		if (isStatusBanned(client) && !isStatusException(client))
		{
			*client << BannedFromChanError(SERVER_NAME, name);
			return false;
		}
		if (channelModes.i == true && !isStatusInvite(client))
		{
			*client << InviteOnlyChanError(SERVER_NAME, name);
			return false;
		}
		if (channelModes.k.compare("") && channelModes.k.compare(password))
		{
			*client << BadChannelKeyError(SERVER_NAME, name);
			return false;
		}
		clientsMap[client] = ChannelClient(client, isChannelOperator);
		if (isChannelOperator)
			addOperator(client->nickname);
		client->joinChannel(this);

		*client <<  TopicReply(SERVER_NAME, name, topic);
		*client <<  ChannelNamesReply(SERVER_NAME, this);

		return true;
	}

	bool	Channel::addServer(Server* server)
	{
		if (serversMap.find(server) != serversMap.end())
			return false;
		serversMap[server] = server;

std::cout << name << ": new server added - number of servers linked to channel = " << serversMap.size() << "\n";

		return true;
	}

	bool	Channel::removeClient(Client* client)
	{
		if (clientsMap.find(client) == clientsMap.end())
			return false;
		client->leaveChannel(this);
		clientsMap.erase(client);

std::cout << "client " << client->nickname << " has been removed from channel " << name << "\n";

		if (clientsMap.empty())
			return close();


		return true;
	}

	bool	Channel::close()
	{
		if (!serversMap.empty())
			serversMap.begin()->second->database->dataChannelsMap.erase(name);
		delete this;

std::cout << "channel " << name << " has been closed\n";

		return true;
	}







// Modes functions

	bool	Channel::addCreator(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(SERVER_NAME, nickname, name);
			return false;
		}
		if (channelModes.O.find(nickname) != channelModes.O.end())
			return false;
		channelModes.O[nickname] = nickname;
		*this << ChannelModeIsReply(SERVER_NAME, name, "+O", nickname);
		return true;
	}
	bool	Channel::removeCreator(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(SERVER_NAME, nickname, name);
			return false;
		}
		if (channelModes.O.find(nickname) == channelModes.O.end())
			return false;
		channelModes.O.erase(nickname);
		*this << ChannelModeIsReply(SERVER_NAME, name, "-O", nickname);
		return true;
	}

	bool	Channel::addOperator(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(SERVER_NAME, nickname, name);
			return false;
		}
		if (channelModes.o.find(nickname) != channelModes.o.end())
			return false;
		channelModes.o[nickname] = nickname;
		*this << ChannelModeIsReply(SERVER_NAME, name, "+o", nickname);
		return true;
	}
	bool	Channel::removeOperator(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.o.find(nickname) == channelModes.o.end())
			return false;
		channelModes.o.erase(nickname);
		*this << ChannelModeIsReply(SERVER_NAME, name, "-o", nickname);
		return true;
	}

	bool	Channel::addVoice(std::string nickname)
	{
		if (!isInChannel(nickname))
		{
			UserNotInChannelError(SERVER_NAME, nickname, name);
			return false;
		}
		if (channelModes.v.find(nickname) != channelModes.v.end())
			return false;
		channelModes.v[nickname] = nickname;
		*this << ChannelModeIsReply(SERVER_NAME, name, "+v", nickname);
		return true;
	}
	bool	Channel::removeVoice(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.v.find(nickname) == channelModes.v.end())
			return false;
		channelModes.v.erase(nickname);
		*this << ChannelModeIsReply(SERVER_NAME, name, "-v", nickname);
		return true;
	}



	bool	Channel::addBanned(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(SERVER_NAME, nickname, name);
		// 	return false;
		// }
		if (channelModes.b.find(nickname) != channelModes.b.end())
			return false;
		channelModes.b[nickname] = nickname;
		*this << BanListReply(SERVER_NAME, name, "+", nickname);
		return true;
	}
	bool	Channel::removeBanned(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(SERVER_NAME, nickname, name);
		// 	return false;
		// }
		if (channelModes.b.find(nickname) == channelModes.b.end())
			return false;
		channelModes.b.erase(nickname);
		*this << BanListReply(SERVER_NAME, name, "-", nickname);
		return true;
	}

	bool	Channel::addException(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(SERVER_NAME, nickname, name);
		// 	return false;
		// }
		if (channelModes.e.find(nickname) != channelModes.e.end())
			return false;
		channelModes.e[nickname] = nickname;
		*this << ExceptionListReply(SERVER_NAME, name, "+", nickname);
		return true;
	}
	bool	Channel::removeException(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(SERVER_NAME, nickname, name);
		// 	return false;
		// }
		if (channelModes.e.find(nickname) == channelModes.e.end())
			return false;
		channelModes.e.erase(nickname);
		*this << ExceptionListReply(SERVER_NAME, name, "-", nickname);
		return true;
	}

	bool	Channel::addInviteList(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(SERVER_NAME, nickname, name);
		// 	return false;
		// }
		if (channelModes.I.find(nickname) != channelModes.I.end())
			return false;
		channelModes.I[nickname] = nickname;
		*this << InviteListReply(SERVER_NAME, name, "+", nickname);
		return true;
	}
	bool	Channel::removeInviteList(std::string nickname)
	{
		// if (!isInChannel(nickname))
		// {
		// 	UserNotInChannelError(SERVER_NAME, nickname, name);
		// 	return false;
		// }
		if (channelModes.I.find(nickname) == channelModes.I.end())
			return false;
		channelModes.I.erase(nickname);
		*this << InviteListReply(SERVER_NAME, name, "-", nickname);
		return true;
	}



}
