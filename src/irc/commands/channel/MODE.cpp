#include <irc/Server.hpp>

namespace irc
{
	Server::ModeCommand::ModeCommand()
		:	ChannelCommand("/mode", true)
	{ }

	bool	Server::ModeCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (arguments.size() < 2)
		{
			*user << NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		std::string nameArgument = arguments[0];
		std::string flags = arguments[1];
		if (!flags.size())
			return false;

		std::string	flagArgument = "";
		if (arguments.size() > 2)
			flagArgument = arguments[2];

		if (!server.database->getClient(nameArgument))
			return server.parseChannelMode(user, nameArgument, flags, flagArgument);
		if (!user->nickname.compare(nameArgument))
			return server.parseUserMode(user, flags, flagArgument);
		*user << UsersDontMatchError(SERVER_NAME);
		return false;

		// Errors/replies not used yet - user

		// Errors/replies not used yet - channel
			// ERR_KEYSET

			// RPL_UNIQOPIS

	}
}
