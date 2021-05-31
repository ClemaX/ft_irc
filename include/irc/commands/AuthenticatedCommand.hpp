#pragma once

#include <irc/commands/ACommand.hpp>

// This is causing problems
#include <irc/Database.hpp>

namespace irc
{
	template<typename Connection>
	struct AuthenticatedCommand
	: public virtual ACommand<Connection>
	{
		AuthenticatedCommand(std::string const& name)
			:	ACommand<Connection>(name)
		{ };

		bool			execute(Database& database, Connection* const user,
			argumentList const& arguments) const throw()
		{
			if (user->authenticated)
				return (payload(database, user, arguments));
			*user << ClientNotResgisteredYet(gHostname);
			return (false);
		}

		virtual bool	payload(Database& database, Connection* const user,
			argumentList const& arguments) const = 0;
	};
}
