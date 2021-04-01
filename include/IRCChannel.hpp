#pragma once

#include <map> // using std::map
#include <set> // using std::set

#include <iostream> // using std::cout // for testing for now

#include <IRCClient.hpp>
#include <IRCServer.hpp>

namespace irc
{

	class Server;
	class Client;
	// TODO: Reference to connection and add ChannelClient on JOIN command
	struct	ChannelClient
	{
		Client*	client;
		bool	isChannelOperator;

		ChannelClient();
		ChannelClient(Client* client);
		ChannelClient(Client* client, bool isOp);
		ChannelClient(const ChannelClient & src);

		ChannelClient & operator=(const ChannelClient & src);
	};

	class	Channel
	{
	protected:
		// typedef std::pair<Client*, ChannelClient> channelClientPair;
		// typedef std::pair<Server*, Server*> channelServerPair;
		std::map<Client*, ChannelClient>	clientsMap;
		std::map<Server*, Server*>	serversMap;

	public:
		std::string const			name;

		Channel();
		Channel(std::string const& name);

		bool	addClient(Client* client, bool	isChannelOperator = false);
		bool	addServer(Server* server);
	};
}
