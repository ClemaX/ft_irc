# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::KillCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		AClient* target;

		if (arguments.size() < 2)
			*user << NeedMoreParamsError(server.hostname, name);
		else if (!user->isOperator())
			*user << NoprivilegesError(server.hostname);
		else
		{
			target = server.database.getClient(arguments.at(0));

			if (!target)
				*user << NoSuchNicknameError(server.hostname, arguments.at(0));
		}

		// msg (arguments.at(1) sent to the target
		// Disconnect the target
	}

}
