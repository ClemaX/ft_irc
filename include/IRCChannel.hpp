#pragma once

#include <list> // using std::list

#include <IRCClient.hpp>


namespace irc
{
	// TODO: Reference to connection and add IRCChannelClient on JOIN command
	struct	IRCChannelClient
	{
		IRCClient*	client;
		bool		isChannelOperator;

		IRCChannelClient(IRCClient* client);
		IRCChannelClient(IRCClient* client, bool isOp);
	};

	class	IRCChannel
	{
	protected:
		std::list<IRCChannelClient>	clients;

	public:
		std::string const			name;

		IRCChannel(std::string const& name);
	};
}
