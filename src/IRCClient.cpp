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
		channel->removeClient(this);
std::cout << "client " << username << " has left channel " << channel->name << "\n";

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

}
