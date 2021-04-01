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

	ChannelClient & ChannelClient::operator=(const ChannelClient & src)
	{
		client = src.client;
		isChannelOperator = src.isChannelOperator;
		return *this;
	}


// --- Channel ---
	Channel::Channel()
		:	clientsMap(), serversMap(), name("")
	{ }

	Channel::Channel(std::string const& name)
		:	clientsMap(), serversMap(), name(name)
	{ }


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
}
