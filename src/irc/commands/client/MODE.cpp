#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::ModeCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
			*user << NeedMoreParamsError(gHostname, name);
		else if (arguments.size() == 1)
		{
			if (server.database.getChannel(arguments.at(0)))
				;//*user ChannelModeIsReply(server.hostname, ); // 324 plamtenz #plamtenz +ns

			else if (server.database.getClient(arguments.at(0)))
			{
				if (arguments.at(0) != user->nickname)
					*user << UsersDontMatchError(server.hostname);
				else
					;//*user << UModeIsReply(server.hostname); // 221 plamtenz +Ri
			}
			else
				*user << NoSuchChannelError(server.hostname, arguments.at(0));
		}
		else
		{
			std::string nameArgument = arguments[0];
			// std::string flags = "";
			// if (arguments.size() > 1)
				std::string flags = arguments[1];
			if (!flags.empty())
			{
				std::string	flagArgument((arguments.size() > 2) ? arguments[2] : "");

				if (!server.database.getClient(nameArgument))
					server.parseChannelMode(user, nameArgument, flags, flagArgument);
				else if (!user->nickname.compare(nameArgument))
					server.parseUserMode(user, flags, flagArgument);
				else
					*user << UsersDontMatchError(gHostname);
			}
		}
	}
}
