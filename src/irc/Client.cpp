#include <irc/Client.hpp>

namespace irc
{

// --- ClientModes ---
	ClientModes::ClientModes()
		:	binMode(0)
	{ }

	ClientModes::~ClientModes() {}


// --- Client ---
	Client::Client(int fd, address const& address,
		bool authenticationRequired)
		:	SocketConnection(fd, address),
			authenticated(!authenticationRequired),
			registered(false)
	{ readBuffer.reserve(IRC_MESSAGE_MAXLEN); } // TODO: Maybe reserve writeBuffer

	Client::~Client() throw()
	{
		leaveAllChannels();
	}

	Client&	Client::operator<<(std::string const& message)
	{
		writeBuffer.append(message);
		return *this;
	}

	Client&	Client::operator<<(NumericReply const& reply)
	{
		*this << reply.serialize();
		return *this;
	}

	Client&	Client::operator<<(PrivateMessage const& reply)
	{
		*this << reply.serialize();
		return *this;
	}

	void	Client::flush() throw(SocketWriteException)
	{
		SocketConnection::operator<<(writeBuffer);
		writeBuffer.clear();
	}

	void	Client::joinChannel(Channel * channel)
	{
		clientChannels.insert(clientChannelPair(channel->name, channel));
	}

	void	Client::leaveChannel(Channel * channel)
	{
		if (clientChannels.find(channel->name) == clientChannels.end())
			return ;
		clientChannels.erase(ft::strToLower(channel->name));
	}

	void	Client::leaveChannel(std::string const & channelName)
	{
		clientChannelMap::iterator it = clientChannels.find(ft::strToLower(channelName));

		if (it == clientChannels.end())
			return ;
		clientChannels.erase(ft::strToLower(channelName));
	}

	void	Client::leaveAllChannels()
	{
		clientChannelMap::iterator it;

		while (!clientChannels.empty())
		{
			it = clientChannels.begin();
			it->second->removeClient(this, "");
		}
	}

	bool	Client::isInChannel(Channel *channel) const
	{return (clientChannels.find(ft::strToLower(channel->name)) != clientChannels.end());}

	bool	Client::isInChannel(std::string const & channelName) const
	{return (clientChannels.find(ft::strToLower(channelName)) != clientChannels.end());}

	bool	Client::isInSameChannel(Client *client) const
	{
		clientChannelMap::const_iterator itb = clientChannels.begin();
		clientChannelMap::const_iterator ite = clientChannels.end();
		while (itb != ite)
		{
			if (client->isInChannel(itb->first))
				return true;
			itb++;
		}
		return false;
	}

	Channel	*Client::getChannel(std::string const & channelName) const
	{
		if (isInChannel(channelName))
			return clientChannels.find(ft::strToLower(channelName))->second;
		return NULL;
	}


	/**
	 * 	@brief Return a pointer to the channel which name is channelName.
	 *
	 * 	@param channelName The name of the channel.
	 *
	 * 	NOTE: The search is done among all the channels in the database
	*/

	Channel	*Client::getChannelGlobal(std::string const & channelName) const
	{
		Channel *channel = getChannel(channelName);
		if (channel)
			return channel;

		channel = server->getChannel(channelName);
		if (!channel)
			return NULL;
		if (!channel->isLocalChannelVisibleForClient(this))
			return NULL;
		return channel;
	}


	void	Client::receiveMessage(Client *client, std::string const &message)	// check if invisible ?
	{
		*this << PrivateMessage(client->nickname, message);
	}


	bool	Client::listChannelInfo(Channel *channel)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName))
		{
			if (channel->channelModes.binMode & M_s)
				return false;
			else if ((channel->channelModes.binMode & M_p) && channel->isVisibleForClient(this))
			{
				*this << ListReply(gHostname, channelName, 0, "Prv");
				return false;
			}
			else if (channel->isLocalChannelVisibleForClient(this))
				*this << ListReply(gHostname, channelName, channel->clientsMap.size(), channel->topic);
			return false;
		}
		else
			*this << ListReply(gHostname, channelName, channel->clientsMap.size(), channel->topic);
		return true;
	}

	bool	Client::listAllChannelsListInfo(void)
	{
		for (IRCDatabase::databaseChannelsMap::const_iterator it = server->database.dataChannelsMap.begin();
			it != server->database.dataChannelsMap.end(); it++)
			this->listChannelInfo(it->second);
		return true;
	}


		bool	Client::listChannelWhoQueryInfo(Channel *channel, int opFlag)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName) &&
			((channel->channelModes.binMode & M_s) || (channel->channelModes.binMode & M_p)))
				return false;
		else
		{
			Channel::channelClientMap::iterator itb = channel->clientsMap.begin();
			Channel::channelClientMap::iterator ite = channel->clientsMap.end();
			while (itb != ite)
			{
				if (!opFlag || channel->isOperator(itb->first))
					*this << WhoReply(gHostname, channelName, itb->first, channel->isOperator(itb->first));
				itb++;
			}
		}
		return true;
	}

	bool	Client::listAllVisibleUsersWhoQueryInfo(void)
	{
		for (IRCDatabase::databaseClientsMap::const_iterator it = server->database.dataClientsMap.begin();
			it != server->database.dataClientsMap.end(); it++)
		{
			Client *client = it->second;
			if (!(client->clientModes.binMode & Mu_i) && !this->isInSameChannel(client))
				*this << WhoReply(gHostname, "", client, -1);
		}
		return true;
	}

	bool	Client::matchMaskWhoQueryInfo(std::string const &mask)
	{
		// currently match with users' host, real name and nickname
		// to do :
		//		match with users' server
		for (IRCDatabase::databaseClientsMap::const_iterator it = server->database.dataClientsMap.begin();
			it != server->database.dataClientsMap.end(); it++)
		{
			Client *client = it->second;
			if (!(client->clientModes.binMode & Mu_i) &&
					(matchPattern_global(client->nickname, mask) ||
					matchPattern_global(client->username, mask) ||
					matchPattern_global(client->hostname, mask)))
				*this << WhoReply(gHostname, "", client, -1);
		}
		return true;
	}

}
