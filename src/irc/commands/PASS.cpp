#include <irc/Server.hpp>

namespace irc
{
	Server::PassCommand::PassCommand()
		:	Command("PASS")
	{ }

	bool	Server::PassCommand::payload(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (arguments.empty())
			*user << NeedMoreParamsError(server.hostname, name);
		else if (user->registered)
			*user << UserAlreadyRegistred(server.hostname, user->nickname);
		else if ((user->authenticated = arguments.at(0) == server.config[IRC_CONF_PASS]))
			return (true);
		return (false);
	}
}
