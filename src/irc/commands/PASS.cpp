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
			*user << NeedMoreParamsError(server.hostname, name);
		else if (user->registered)
			*user << UserAlreadyRegistred(server.hostname, user->nickname);
		else if (arguments.at(0) == server.config[IRC_CONF_PASS])
		{
			user->authenticated = true;
			return (true);
		}
		else
			user->authenticated = false;
		return (false);
	}
}
