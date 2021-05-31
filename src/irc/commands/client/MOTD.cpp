#include <irc/commands/ClientCommands.hpp>

#include <utils/Logger.hpp>

namespace NAMESPACE_IRC
{
	bool
	MotdCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		if (!user->registered)
		{
			*user << ClientNotResgisteredYet(database.hostname);
			return (false);
		}

		Logger::instance() << Logger::DEBUG << user->username << " executes " << name << std::endl;

		*user << serializeReplyList<MotdStartReply, MotdReply, EndOfMotdReply>(
			gHostname, user->nickname, database.motd, '\n', 80);

		if (arguments.size())
		{
			// TODO: Route to database
			std::cout << "Arguments: ";
			for (argumentList::const_iterator it = arguments.begin();
				it != arguments.end(); it++)
				std::cout << *it << ", ";
			std::cout << std::endl;
		}
		return false;
	}
}
