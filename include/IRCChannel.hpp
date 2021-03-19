#pragma once

#include <list> // using std::list

#include <IRCClient.hpp>


namespace irc
{
	// TODO: Reference to connection and add IRCChannelClient on JOIN command
	struct	IRCChannelClient	:	IRCClient
	{
		bool	isChannelOperator;

		IRCChannelClient(struct sockaddr_in const& address);
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
