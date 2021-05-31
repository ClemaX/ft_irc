#include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	ModeCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
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

		if (!database.getClient(nameArgument))
			return database.parseChannelMode(user, nameArgument, flags, flagArgument);
		if (!user->nickname.compare(nameArgument))
			return database.parseUserMode(user, flags, flagArgument);
		*user << UsersDontMatchError(gHostname);
		return false;
	}
}
