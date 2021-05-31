#pragma once

#include <irc/commands/ACommand.hpp>
#include <irc/ABufferedConnection.hpp>

namespace irc
{
	struct UnauthenticatedCommand
		: public ACommand<ABufferedConnection>
	{
		UnauthenticatedCommand(std::string const& name)
			:	ACommand(name)
		{ }
	};
}
