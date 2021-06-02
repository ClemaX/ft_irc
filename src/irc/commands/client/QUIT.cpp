# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::QuitCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		static_cast<void>(server);
		static_cast<void>(user);
		static_cast<void>(arguments);
		return (true);
	}

}
