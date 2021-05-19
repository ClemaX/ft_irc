#include <irc/Client.hpp>

namespace NAMESPACE_IRC
{

// --- Client ---

	// It is worth to redo Client class with templates to avoid
	// forward refereneces and define those 2 in hpp ??

	/* inline */ void
	Client::joinChannel(__Channel* const channel)
	{ clientChannels.insert(clientChannelPair(channel->name, channel)); }

	/* inline */ bool
	Client::isInChannel(__Channel* const channel) const
	{ return (clientChannels.find(ft::strToLower(channel->name)) != clientChannels.end()); }

	Client::Client(int fd, address const& address,
		bool authenticationRequired)
		:	SocketConnection(fd, address),
			authenticated(!authenticationRequired),
			registered(false)
	{ readBuffer.reserve(IRC_MESSAGE_MAXLEN); } // TODO: Maybe reserve writeBuffer


	void	Client::leaveChannel(__Channel* const channel)
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

	bool	Client::isInSameChannel(Client* const client) const
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

	Client::__Channel	*Client::getChannel(std::string const & channelName) const
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

	Client::__Channel	*Client::getChannelGlobal(std::string const & channelName) const
	{
		__Channel *channel = getChannel(channelName);
		if (channel)
			return channel;

		channel = server->getChannel(channelName);
		if (!channel)
			return NULL;
		if (!channel->isLocalChannelVisibleForClient(const_cast<Client*>(this)))
			return NULL;
		return channel;
	}

	bool	Client::listChannelInfo(__Channel* const channel)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName))
		{
			if (channel->channelModes.binMode & M_s)
				return false;
			else if (channel->channelModes.binMode & M_p)
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


		bool	Client::listChannelWhoQueryInfo(__Channel* const channel, int opFlag)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName) &&
			((channel->channelModes.binMode & M_s) || (channel->channelModes.binMode & M_p)))
				return false;
		else
		{
			__Channel::channelClientMap::iterator itb = channel->clientsMap.begin();
			__Channel::channelClientMap::iterator ite = channel->clientsMap.end();
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
