#include <irc/Server.hpp>

namespace irc
{
	Server::PassCommand::PassCommand()
		:	Command("PASS")
	{ }

	bool	Server::PassCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (arguments.empty())
		{
			*user << NeedMoreParamsError(server.hostname, name);
			goto error;
		}

		if (user->first_connection == false)
		{
			*user << UserAlreadyRegistred(server.hostname, user->nickname);
			goto error;
		}

		// Just set the password here.

		return (true);

		error:
		return (false);
	}
}
