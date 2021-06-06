# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::KillCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		AClient* target = NULL;

		if (arguments.size() < 2)
			*user << NeedMoreParamsError(server.hostname, name);
		else if (!user->isOperator())
			*user << NoprivilegesError(server.hostname);
		else
		{
			target = server.database.getClient(arguments.at(0));

			if (!target)
			{
				if (arguments.at(0) == server.hostname)
					*user << CanKillServerError(server.hostname);
				else
					*user << NoSuchNicknameError(server.hostname, arguments.at(0));
			}
		}
		if (target)
		{
			*target << arguments.at(1);
			server.disconect_client(target);
		}
	}
}
