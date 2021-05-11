#include <irc/Server.hpp>

namespace irc
{
	Server::WhoQuery::WhoQuery()
		:	Command("WHO")
	{ }

	bool	Server::WhoQuery::payload(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!user->registered)
		{
			*user << ClientNotResgisteredYet(server.hostname);
			return (false);
		}

		std::string mask = "";
		if (!arguments.size() || !arguments[0].compare("0") || !arguments[0].compare("*"))
			user->listAllVisibleUsersWhoQueryInfo();
		else
		{
			mask = arguments[0];
			int	opFlag = 0;
			if (arguments.size() > 1 && !arguments[1].compare("o"))
				opFlag = 1;

			Channel *channel = server.database.getChannel(mask);
			if (channel)
				user->listChannelWhoQueryInfo(channel, opFlag);
			else
				user->matchMaskWhoQueryInfo(mask);
		}
		*user << EndOfWhoReply(gHostname, mask);
		return true;
	}
}
