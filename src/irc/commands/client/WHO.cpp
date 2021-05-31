#include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	WhoQuery::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		if (!user->registered)
		{
			*user << ClientNotResgisteredYet(database.hostname);
			return (false);
		}

		std::string mask = "";
		if (!arguments.size() || !arguments[0].compare("0") || !arguments[0].compare("*"))
			user->listAllVisibleUsersWhoQueryInfo(database);
		else
		{
			mask = arguments[0];
			int	opFlag = 0;
			if (arguments.size() > 1 && !arguments[1].compare("o"))
				opFlag = 1;

			Channel *channel = database.getChannel(mask);
			if (channel)
				user->listChannelWhoQueryInfo(channel, opFlag);
			else
				user->matchMaskWhoQueryInfo(database, mask);
		}
		*user << EndOfWhoReply(gHostname, mask);
		return true;
	}
}
