#include <irc/Server.hpp>

namespace irc
{
	// --- USER --- //

	Server::UserCommand::UserCommand()
	: Command("USER")
	{ }

	bool
	Server::UserCommand::
	payload(Server& server, Client* user,argumentList const& arguments) const
	{
		// ERR_NEEDMOREPARAMS Bad amount of params
		if (arguments.size() < 4)
		{
			*user << NeedMoreParamsError(server.hostname, name);
			goto error;
		}

		// ERR_ALREADYREGISTRED User already exists
		if (user->registered)
		{
			*user << UserAlreadyRegistred(server.hostname, user->nickname);
			goto error;
		}

		user->username = arguments.at(0);
		user->hostname = arguments.at(1);
		user->servername = arguments.at(2);
		user->realname = arguments.at(3);

		server.announceWelcomeSequence(user);

		return (true);

		error:
		return (false);

	}
}
