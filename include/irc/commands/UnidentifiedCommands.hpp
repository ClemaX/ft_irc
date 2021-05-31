#pragma once

#include <irc/commands/UnauthenticatedCommand.hpp>
#include <irc/commands/AuthenticatedCommand.hpp>

namespace irc
{
	struct PassCommand
		: public UnauthenticatedCommand
	{
		PassCommand()
			:	UnauthenticatedCommand("PASS")
		{ }

		bool payload(Database &database, ABufferedConnection *const user,
					argumentList const &arguments) const;
	};

	struct ServerServerCommand
		:	AuthenticatedCommand<ABufferedConnection>
	{
		ServerServerCommand()
			:	AuthenticatedCommand<ABufferedConnection>("SERVER")
		{ }

		bool	payload(Database& database, ABufferedConnection* const user,
			argumentList const& arguments) const;
	};
}
