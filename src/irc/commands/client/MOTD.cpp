#include <irc/Server.hpp>

#include <utils/Logger.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::MotdCommand::
	payload(Server& server, Client* const user, argumentList const& arguments) const
	{
		if (!user->registered)
		{
			*user << ClientNotResgisteredYet(server.hostname);
			return (false);
		}

		Logger::instance() << Logger::DEBUG << user->username << " executes " << name << std::endl;

		*user << serializeReplyList<MotdStartReply, MotdReply, EndOfMotdReply>(
			gHostname, user->nickname, server.config["MOTD"], '\n', 80);

		if (arguments.size())
		{
			// TODO: Route to server
			std::cout << "Arguments: ";
			for (argumentList::const_iterator it = arguments.begin();
				it != arguments.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
		return false;
	}
}
