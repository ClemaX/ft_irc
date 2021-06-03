# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::QuitCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		// TODO: Implement QuitCommand
		static_cast<void>(server);
		static_cast<void>(user);
		static_cast<void>(arguments);
	}

}
