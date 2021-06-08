#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::ModeCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		// if (arguments.size() < 1)
		if (arguments.size() < 2)
			*user << NeedMoreParamsError(gHostname, name);
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
