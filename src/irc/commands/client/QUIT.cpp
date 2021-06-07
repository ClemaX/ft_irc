# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::QuitCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
			*user << user->nickname + " has quit the server: " + server.hostname << IRC_MESSAGE_SUFFIX;
		else
			*user << arguments.at(0) + IRC_MESSAGE_SUFFIX;
		server.disconect_client(user);
	}
}
