# include <irc/Server.hpp>
# include <irc/replies/CommandReplies.hpp>
# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::TimeCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		// No given args, use client's server
		if (arguments.empty())
			*user << Time(server.hostname, server.get_local_time());
		else
		{
			// TODO: Remove server search if we got only one
			// Given args, search the server and output it version
			Server::serversMap::const_iterator it = server.database.dataServersMap.begin();

			while (it != server.database.dataServersMap.end())
			{
				if (it->second->hostname == arguments.at(0))
				{
					*user << Time(it->second->hostname, it->second->get_local_time());
					return;
				}
				++it;
			}

			// No match ?
			*user << NoSuchServerError(arguments.at(0));
		}
	}
}
