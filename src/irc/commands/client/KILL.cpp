# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::KillCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		AClient* target;

		if (arguments.size() < 2)
		{
			// Empty msg
			*user << NeedMoreParamsError(server.hostname, name);
			goto error;
		}

		if (user->isOperator() == false)
		{
			*user << NoprivilegesError(server.hostname);
			goto error;
		}

		target = server.database.getClient(arguments.at(0));
		if (!target)
		{
			*user << NoSuchNicknameError(server.hostname, arguments.at(0));
			goto error;
		}

		// msg (arguments.at(1) sent to the target
		// Disconnect the target

		return (true);

		error:

		return (false);
	}

}
