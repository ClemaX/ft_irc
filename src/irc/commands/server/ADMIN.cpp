# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	namespace
	{
		inline void
		display_admin_data(const Server& server, AClient* const user)
		{
			*user << AdminMeReply(server.get_hostname(), server.admin.id.first);
			*user << AdminLoc1Reply(server.get_hostname(), server.admin.data1);
			*user << AdminLoc2Reply(server.get_hostname(), server.admin.data2);
			*user << AdminEmailReply(server.get_hostname(), server.admin.email);
		}
	}

	bool
	Server::AdminCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
		{
			// TODO: Get the user's server or check if this is handled by relay
			display_admin_data(server, user);
			return (true);
		}
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
		// No match ?
		*user << NoSuchServerError(arguments.at(0));
		return (false);
	}
}