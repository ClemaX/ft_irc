# include <irc/Server.hpp>
# include <irc/replies/CommandReplies.hpp>
# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::VersionCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		// FIXME: No given args, use client's server
		if (arguments.empty())
			*user << Version(server.hostname, server.version);
		else
		{
			// TODO: Remove this if we do not use multiple servers
			// Given args, search the server and output it version
			Server::serversMap::const_iterator it = server.database.dataServersMap.begin();

			while (it != server.database.dataServersMap.end())
			{
				if (it->second->hostname == arguments.at(0))
				{
					*user << Version(it->second->hostname, it->second->version);
					return;
				}
				++it;
			}

			// No match ?
			*user << NoSuchServerError(arguments.at(0));
		}
	}
}
