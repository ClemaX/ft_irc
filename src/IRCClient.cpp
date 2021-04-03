#include <IRCClient.hpp>

namespace irc
{
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
		if (clientChannels.find(channel->name) != clientChannels.end())
			return ;
		clientChannels.insert(clientChannelPair(channel->name, channel));

std::cout << "client " << username << " has joined channel " << channel->name << "\n";

	}

	void	Client::leaveChannel(Channel * channel)
	{
		if (clientChannels.find(channel->name) == clientChannels.end())
			return ;
		clientChannels.erase(channel->name);
std::cout << "client " << username << " has left channel " << channel->name << "\n";
		channel->removeClient(this);
	}

	void	Client::leaveChannel(std::string const & name)
	{
		clientChannelMap::iterator it = clientChannels.find(name);
		Channel *channel;

		if (it == clientChannels.end())
			return ;
		channel = it->second;
		clientChannels.erase(name);
std::cout << "client " << username << " has left channel " << channel->name << "\n";
		channel->removeClient(this);
	}

	void	Client::leaveAllChannels()
	{
		clientChannelMap::iterator it;

		while (!clientChannels.empty())
		{
			it = clientChannels.begin();
			leaveChannel((*it).second);
		}
	}

	bool	Client::isInChannel(Channel *channel) const
	{return (clientChannels.find(channel->name) != clientChannels.end());}

	bool	Client::isInChannel(std::string const & channelName) const
	{return (clientChannels.find(channelName) != clientChannels.end());}

	Channel	*Client::getChannel(std::string const & channelName) const
	{
		if (isInChannel(channelName))
			return clientChannels.find(channelName)->second;
		return NULL;
	}

}
