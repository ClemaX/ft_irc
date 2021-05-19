#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool	Server::ModeCommand::payload(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (arguments.size() < 2)
		{
			*user << NeedMoreParamsError(gHostname, name);
			return false;
		}

		std::string nameArgument = arguments[0];
		std::string flags = arguments[1];
		if (flags.empty())
			return false;

		std::string	flagArgument = "";
		if (arguments.size() > 2)
			flagArgument = arguments[2];

		if (!server.database.getClient(nameArgument))
			return server.parseChannelMode(user, nameArgument, flags, flagArgument);
		if (!user->nickname.compare(nameArgument))
			return server.parseUserMode(user, flags, flagArgument);
		*user << UsersDontMatchError(gHostname);
		return false;
	}
}