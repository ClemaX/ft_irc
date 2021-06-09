#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	// --- USER --- //

	void
	Server::UserCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.size() < 4) // ERR_NEEDMOREPARAMS Bad amount of params
			*user << NeedMoreParamsError(server.hostname, name);
		else if (user->registered) // ERR_ALREADYREGISTRED User already exists
			*user << UserAlreadyRegistred(server.hostname, user->nickname);
		else
		{
			user->username = arguments.at(0);
			user->hostname = user->getHostname();
			user->servername = server.hostname;
			user->realname = arguments.at(3);

			server.announceWelcomeSequence(user);
		}
	}
}
