#include <irc/Client.hpp>

namespace irc
{

// --- ClientModes ---
	ClientModes::ClientModes()
		:	i(false), s(false), w(false), o(false)
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
		if (channel->channelModes.p == false && channel->channelModes.s == false)
			return channel;
		return NULL;
	}

}
