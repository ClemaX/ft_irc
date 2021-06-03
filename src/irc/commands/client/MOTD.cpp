#include <irc/Server.hpp>

#include <utils/Logger.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::MotdCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		*user << serializeReplyList<MotdStartReply, MotdReply, EndOfMotdReply>(
			gHostname, user->nickname, server.config["MOTD"], '\n', 80);

		if (arguments.size())
		{
			// TODO: Route to server / Since we only have one server just check matching servername
			std::cout << "Arguments: ";
			for (argumentList::const_iterator it = arguments.begin();
				it != arguments.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
	}
}
