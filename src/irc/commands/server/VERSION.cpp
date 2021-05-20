# include <irc/Server.hpp>
# include <irc/replies/CommandReplies.hpp>
# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::VersionCommand::
	payload(Server& server, Client* const user, argumentList const& arguments) const
	{
		// No given args, use client's server
		if (arguments.empty())
		{
			*user << Version(server.hostname, user->server->version);
			return (true);
		}

		// Given args, search the server and output it version
		Server::serversMap::const_iterator it = server.database.dataServersMap.begin();

		while (it != server.database.dataServersMap.end())
		{
			if (it->second->hostname == arguments.at(0))
			{
				*user << Version(it->second->hostname, it->second->version);
				return (true);
			}
			++it;
		}

		// No match ?
		*user << NoSuchServerError(arguments.at(0));
		return (false);
	}
}
