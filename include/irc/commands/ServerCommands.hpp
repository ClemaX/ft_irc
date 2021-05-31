#pragma once

#include <irc/commands/ServerCommand.hpp>

namespace irc
{

	struct SquitServerCommand
	: ServerCommand
	{
		SquitServerCommand()
			:	ServerCommand("SQUIT")
		{ }

		bool	payload(Database& database, AServerConnection* const user,
			argumentList const& arguments) const;
	};
}
