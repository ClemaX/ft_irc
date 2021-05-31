#include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	// --- USER --- //

	bool
	UserCommand::
	payload(Database& database, AClient* const user,argumentList const& arguments) const
	{
		// ERR_NEEDMOREPARAMS Bad amount of params
		if (arguments.size() < 4)
		{
			*user << NeedMoreParamsError(database.hostname, name);
			goto error;
		}

		// ERR_ALREADYREGISTRED User already exists
		if (user->registered)
		{
			*user << UserAlreadyRegistred(database.hostname, user->nickname);
			goto error;
		}

		user->username = arguments.at(0);
		user->hostname = arguments.at(1);
		user->servername = arguments.at(2);
		user->realname = arguments.at(3);

		user->welcome(database);

		return (true);

		error:
		return (false);

	}
}
