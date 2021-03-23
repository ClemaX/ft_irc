#pragma once

#include <list> // using std::list

#include <IRCClient.hpp>


namespace irc
{
	// TODO: Reference to connection and add ChannelClient on JOIN command
	struct	ChannelClient
	{
		Client*	client;
		bool		isChannelOperator;

		ChannelClient(Client* client);
		ChannelClient(Client* client, bool isOp);
	};

	class	Channel
	{
	protected:
		std::list<ChannelClient>	clients;

	public:
		std::string const			name;

		Channel(std::string const& name);
	};
}
