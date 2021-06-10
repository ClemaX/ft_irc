# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::AdminCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{

		// TODO: Get the user's server or check if this is handled by relay
		if (arguments.empty())
		{
			*user << AdminMeReply(server.get_hostname(), server.config[IRC_CONF_ADMIN_NICK]);
			*user << AdminLoc1Reply(server.get_hostname(), server.config[IRC_CONF_ADMIN_DATA1]);
			*user << AdminLoc2Reply(server.get_hostname(), server.config[IRC_CONF_ADMIN_DATA2]);
			*user << AdminEmailReply(server.get_hostname(), server.config[IRC_CONF_ADMIN_EMAIL]);
		}
		else // TODO: Handle local server name and reject others
			*user << NoSuchServerError(arguments.at(0));
/*
		// Given args, search the server and output it version
		Server::serversMap::const_iterator it = server.database.dataServersMap.begin();

	 	while (it != server.database.dataServersMap.end())
		{
			// TODO: This should be servername
			if (it->second->hostname == arguments.at(0))
			{
				display_admin_data(*it->second, user);
				return (true);
			}
			++it;
		}
 */
	}
}
