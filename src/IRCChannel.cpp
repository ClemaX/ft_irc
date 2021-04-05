#include <IRCChannel.hpp>

namespace irc
{

// --- ChannelClient ---
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

// --- ChannelModes ---
	ChannelModes::ChannelModes()
		:	o(), p(false), s(false), i(false), t(false), n(false),
			m(false), l(false), b(), v(), k()
	{ }	

	ChannelModes::~ChannelModes() {}


// --- Channel ---
	Channel::Channel()
		:	clientsMap(), serversMap(), topic(""), channelModes(), name("")
	{ }

	Channel::Channel(std::string const& name)
		:	clientsMap(), serversMap(), topic(""), channelModes(), name(name)
	{ }
	
	Channel::~Channel() {}

	// ChannelModes	Channel::getModes() const
	// {return channelModes;}

	std::string	Channel::getTopic() const
	{return topic;}

	void	Channel::setTopic(const std::string & str)
	{topic = str;}

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

	bool	Channel::isOperator(Client *client) const
	{return (channelModes.o.find(client->nickname) != channelModes.o.end());}

	bool	Channel::isOperator(std::string const & clientNickname) const
	{return (channelModes.o.find(clientNickname) != channelModes.o.end());}
	// is in channel necessary ?

	Client* Channel::getUser(std::string const & clientNickname) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
		{
			if (it->first->nickname == clientNickname)
				return it->first;
		}
		return NULL;
	}

	void	Channel::displayNicknames(void) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
			std::cout << it->first->nickname << "\n";
	}

	bool	Channel::addClient(Client* client, bool	isChannelOperator)
	{
		if (clientsMap.find(client) != clientsMap.end())
			return false;
		if (channelModes.l > 0 && clientsMap.size() >= channelModes.l)
			return false;
		clientsMap[client] = ChannelClient(client, isChannelOperator);
		if (isChannelOperator)
			addOperator(client->nickname);

std::cout << name << ": new client added - number of clients in channel = " << clientsMap.size() << "\n";
	
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
		client->clientChannels.erase(name);
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




	// Modes functions	// left to code

	bool	Channel::addOperator(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;	// is it possible to set a user not present in the channel as an operator ?
		if (channelModes.o.find(nickname) != channelModes.o.end())
			return false;
		channelModes.o[nickname] = nickname;
std::cout << "channel " << name << " has added " << nickname << " as a new operator!\n";
		return true;
	}
	bool	Channel::removeOperator(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.o.find(nickname) == channelModes.o.end())
			return false;
		channelModes.o.erase(nickname);
std::cout << "channel " << name << " has removed " << nickname << " from the operator map!\n";
		return true;
	}
	
	bool	Channel::addBanned(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;	// is it possible to ban a user not present in the channel ?
		if (channelModes.b.find(nickname) != channelModes.b.end())
			return false;
		channelModes.b[nickname] = nickname;
std::cout << "channel " << name << " has banned " << nickname << "!\n";
		return true;
	}
	bool	Channel::removeBanned(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.b.find(nickname) == channelModes.b.end())
			return false;
		channelModes.b.erase(nickname);
std::cout << "channel " << name << " has removed " << nickname << " from the banned users!\n";
		return true;
	}
	
	bool	Channel::addVoice(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;	// is it possible to add a user not present in the channel in the voice map ?
		if (channelModes.v.find(nickname) != channelModes.v.end())
			return false;
		channelModes.v[nickname] = nickname;
std::cout << "channel " << name << " has added " << nickname << " in the voice map!\n";
		return true;
	}
	bool	Channel::removeVoice(std::string nickname)
	{
		if (!isInChannel(nickname))
			return false;
		if (channelModes.v.find(nickname) == channelModes.v.end())
			return false;
		channelModes.v.erase(nickname);
std::cout << "channel " << name << " has removed " << nickname << " from the voice map!\n";
		return true;
	}
}
