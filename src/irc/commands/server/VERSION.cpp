# include <irc/Server.hpp>
# include <irc/replies/CommandReplies.hpp>
# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::VersionCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		static_cast<void>(arguments);
		*user << Version(server.hostname, server.version);
	}
}
