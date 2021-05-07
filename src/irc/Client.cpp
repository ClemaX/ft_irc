#include <irc/Client.hpp>

namespace irc
{

// --- ClientModes ---
	ClientModes::ClientModes()
		:	i(false), s(false), w(false), o(false)
	{ }

	ClientModes::~ClientModes() {}


// --- Client ---
	Client::Client(int fd, address const& address)
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

	void	Client::flush() throw(SocketWriteException)
	{
		SocketConnection::operator<<(writeBuffer);
		writeBuffer.clear();
	}

	void	Client::joinChannel(Channel * channel)
	{
		clientChannels.insert(clientChannelPair(channel->name, channel));
std::cout << "client " << username << " has joined channel " << channel->name << "\n";
	}

	void	Client::leaveChannel(Channel * channel)
	{
		if (clientChannels.find(channel->name) == clientChannels.end())
			return ;
		clientChannels.erase(channel->name);
std::cout << "client " << username << " has left channel " << channel->name << "\n";
	}

	void	Client::leaveChannel(std::string const & channelName)
	{
		clientChannelMap::iterator it = clientChannels.find(ft::strToLower(channelName));
		Channel *channel;

		if (it == clientChannels.end())
			return ;
		channel = it->second;
		clientChannels.erase(ft::strToLower(channelName));
std::cout << "client " << username << " has left channel " << channel->name << "\n";
		channel->removeClient(this);
	}

	void	Client::leaveAllChannels()
	{
		clientChannelMap::iterator it;

		while (!clientChannels.empty())
		{
			it = clientChannels.begin();
			(*it).second->removeClient(this);
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

	bool	Client::listChannelInfo(Channel *channel)
	{
		if (!channel)
			return false;

		std::string const &channelName = channel->name;

		if (!isInChannel(channelName))
		{
			if (channel->channelModes.s == true)
				return false;
			if (channel->channelModes.p == true)
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
