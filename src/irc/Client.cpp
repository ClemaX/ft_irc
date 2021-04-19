#include <irc/Client.hpp>

namespace irc
{

// --- ClientModes ---
	ClientModes::ClientModes()
		:	binMode(0)
	{ }

	ClientModes::~ClientModes() {}


// --- Client ---
	Client::Client(int fd, struct sockaddr_in const& address)
		:	SocketConnection(fd, address)
	{ readBuffer.reserve(IRC_MESSAGE_MAXLEN); } // TODO: Maybe reserve writeBuffer

	Client::~Client() throw()
	{
		leaveAllChannels();
	}

	Client const&	Client::operator<<(std::string const& message)
	{
		writeBuffer.append(message);
		return *this;
	}

	Client const&	Client::operator<<(NumericReply const& reply)
	{
		*this << reply.serialize();
		return *this;
	}

	Client const&	Client::operator<<(PrivateMessage const& reply)
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

		IRCDatabase::databaseChannelsMap channelMap = server->database->dataChannelsMap;
		IRCDatabase::databaseChannelsMap::const_iterator it = channelMap.find(ft::strToLower(channelName));
		if (it == channelMap.end())
			return NULL;
		channel = it->second;
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
			if (channel->channelModes.binMode & M_p)
			{
				*this << ListReply(SERVER_NAME, channelName, 0, "Prv");
				return false;
			}
		}
		*this << ListReply(SERVER_NAME, channelName, channel->clientsMap.size(), channel->topic);
		return true;
	}

	bool	Client::listAllChannelsInfo(void)
	{
		server->database->displayAllChannelsInfo(this);
		return true;
	}
}
