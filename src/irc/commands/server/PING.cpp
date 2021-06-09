#include <irc/Server.hpp>

#include <irc/replies/AReply.hpp>

namespace NAMESPACE_IRC
{
	struct PongReply: public AReply
	{
		PongReply(std::string const &prefix, std::string const& hostname, std::string const& tag)
		:AReply(prefix)
		{
			message += "PONG" + std::string(" ") + hostname + " " + ":" + tag;
		}
	};

	void
	Server::PingCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
			*user << NeedMoreParamsReply(server.hostname);

		*user << PongReply(server.hostname, server.hostname, arguments[0]);
	}
}
