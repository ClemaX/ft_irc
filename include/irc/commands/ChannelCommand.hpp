#pragma once

#include <irc/commands/ClientCommand.hpp>
#include <irc/commands/AuthenticatedCommand.hpp>

namespace irc
{
	struct ChannelCommand
	: public ClientCommand
	{
		bool const	isOperatorCommand;

		ChannelCommand(std::string const& name, bool isOperatorCommand)
			: ClientCommand(name), isOperatorCommand(isOperatorCommand)
		{ }
		// TODO: Add execution check
	};
}
