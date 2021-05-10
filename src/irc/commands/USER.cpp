#include <irc/Server.hpp>

namespace irc
{
	// --- USER --- //

	Server::UserCommand::UserCommand()
	: Command("USER")
	{ }

	bool
	Server::UserCommand::
	execute(Server& server, Client* user,argumentList const& arguments) const
	{
		// ERR_NEEDMOREPARAMS Bad amount of params
		if (arguments.size() < 4)
		{
			*user << NumericReply(server.hostname, ERR_NEEDMOREPARAMS);
			goto error;
		}

		// ERR_ALREADYREGISTRED User already exists
		if (!user->username.empty())
		{
			*user << NumericReply(server.hostname, ERR_ALREADYREGISTRED);
			goto error;
		}

		user->username = arguments.at(0);
		user->hostname = arguments.at(1);
		user->servername = arguments.at(2);
		user->realname = arguments.at(3);

		*user
		<< WelcomeReply(server.hostname, user->nickname, user->username, user->hostname)
		<< YourHostReply(server.hostname, SERVER_VERSION)
		<< CreatedReply(server.hostname, "") // TO DO: Add time (has a time format i guess)
		<< MyInfoReply(server.hostname, SERVER_VERSION, "", ""); // TO DO: <servername> <version> <available user modes> <available channel modes>

		return (true);

		error:
		return (false);

	}
}
