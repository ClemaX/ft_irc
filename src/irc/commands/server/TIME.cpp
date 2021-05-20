# include <irc/Server.hpp>
# include <irc/replies/CommandReplies.hpp>
# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::TimeCommand::
	payload(Server& server, Client* const user, argumentList const& arguments) const
	{
		// No given args, use client's server
		if (arguments.empty())
		{
			*user << Time(server.hostname, server.get_local_time());
			return (true);
		}

		// Given args, search the server and output it version
		Server::serversMap::const_iterator it = server.database.dataServersMap.begin();

		while (it != server.database.dataServersMap.end())
		{
			if (it->second->hostname == arguments.at(0))
			{
				*user << Time(it->second->hostname, it->second->get_local_time());
				return (true);
			}
			++it;
		}

		// No match ?
		*user << NoSuchServerError(arguments.at(0));
		return (false);
	}
}
