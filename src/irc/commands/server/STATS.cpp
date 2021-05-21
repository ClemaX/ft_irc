# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::StatsCommand::
	payload(Server& server, Client* const user, argumentList const& arguments) const
	{
		static_cast<void>(server);
		static_cast<void>(user);
		static_cast<void>(arguments);
		return (true);

		static const char* const queries[] = {
			"c", "h", "i", "k", "l", "m", "o", "y", "u"
		};

		static_cast<void>(queries);

		// TO DO: Pointer functions responding for each query
	}
}
