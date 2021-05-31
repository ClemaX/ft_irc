#pragma once

#include <irc/commands/AuthenticatedCommand.hpp>
#include <irc/AServerConnection.hpp>

// TODO: Use this for all database comamnds and user AuthenticatedComamnd base

namespace	irc
{
	struct ServerCommand	:	public AuthenticatedCommand<AServerConnection>
	{
		ServerCommand(std::string const& name)
			:	AuthenticatedCommand(name)
		{ }
	};
}
