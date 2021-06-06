# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::QuitCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
			*user << user->nickname + " has quit the server: " + server.hostname;
		else
			*user << arguments.at(0);
		server.disconect_client(user);
	}
}
