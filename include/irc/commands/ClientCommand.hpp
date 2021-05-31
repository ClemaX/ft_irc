#pragma once

#include <irc/commands/AuthenticatedCommand.hpp>
#include <irc/AClient.hpp>

namespace irc
{
	// TODO: Check if this should be virtual
	// TODO: Maybe use typedef instead of creating empty virtual layer
	struct	ClientCommand	:	public AuthenticatedCommand<AClient>
	{
		ClientCommand(std::string const& name)
			:	AuthenticatedCommand<AClient>(name)
		{ }
	};
}
