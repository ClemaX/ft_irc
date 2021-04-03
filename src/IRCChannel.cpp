#include <IRCChannel.hpp>

namespace irc
{

// --- ChannelClient ---
	ChannelClient::ChannelClient()
		:	client(NULL), isChannelOperator(false)
	{ }

	ChannelClient::ChannelClient(Client* client, bool isOp)
		:	client(client), isChannelOperator(isOp)
	{ }

	ChannelClient::ChannelClient(Client* client)
		:	client(client), isChannelOperator(false)
	{ }

	ChannelClient::ChannelClient(const ChannelClient & src)
	{*this = src;}

	ChannelClient::~ChannelClient() {}

	ChannelClient & ChannelClient::operator=(const ChannelClient & src)
	{
		client = src.client;
		isChannelOperator = src.isChannelOperator;
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
		:	clientsMap(), serversMap(), channelModes(), topic(""), name("")
	{ }

	Channel::Channel(std::string const& name)
		:	clientsMap(), serversMap(), channelModes(), topic(""), name(name)
	{ }
	
	Channel::~Channel() {}

	ChannelModes	Channel::getModes() const
	{return channelModes;}

	std::string	Channel::getTopic() const
	{return topic;}

	void	Channel::setTopic(const std::string & str)
	{topic = str;}

	bool	Channel::isInChannel(Client *client) const
	{return (clientsMap.find(client) != clientsMap.end());}

	bool	Channel::isInChannel(std::string const & clientUsername) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
		{
			if (it->first->username == clientUsername)
				return true;
		}
		return false;
	}

	bool	Channel::isOperator(Client *client) const
	{return (isInChannel(client) && clientsMap.find(client)->second.isChannelOperator);}

	Client* Channel::getUser(std::string const & clientUsername) const
	{
		for (channelClientMap::const_iterator it = clientsMap.begin(); it != clientsMap.end(); it++)
		{
			if (it->first->username == clientUsername)
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
		clientsMap[client] = ChannelClient(client, isChannelOperator);

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

std::cout << "client " << client->username << " has been removed from channel " << name << "\n";
		
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
}
