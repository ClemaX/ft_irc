#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::WhoQuery::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (!user->registered)
		{
			*user << ClientNotResgisteredYet(server.hostname);
			return (false);
		}

		std::string mask = "";
		if (!arguments.size() || !arguments[0].compare("0") || !arguments[0].compare("*"))
			user->listAllVisibleUsersWhoQueryInfo(server.database);
		else
		{
			mask = arguments[0];
			int	opFlag = 0;
			if (arguments.size() > 1 && !arguments[1].compare("o"))
				opFlag = 1;

			Server::__Channel *channel = server.database.getChannel(mask);
			if (channel)
				user->listChannelWhoQueryInfo(channel, opFlag);
			else
				user->matchMaskWhoQueryInfo(server.database, mask);
		}
		*user << EndOfWhoReply(gHostname, mask);
		return true;
	}
}
