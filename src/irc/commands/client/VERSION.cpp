# include <irc/commands/ClientCommands.hpp>
# include <irc/replies/CommandReplies.hpp>
# include <irc/replies/ErrorReplies.hpp>

namespace NAMESPACE_IRC
{
	bool
	VersionCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		// FIXME: No given args, use client's server
		if (arguments.empty())
		{
			// TODO: Add version to database?
			*user << Version(database.hostname, "TODO");
			return (true);
		}

		// Given args, search the database and output it version
		//Database::serverMap::const_iterator it = database.servers.begin();

		// TODO: These commands should only match the current server
		// else we need to redirect the query to the correct ServerConnection
		/* while (it != database.servers.end())
		{
			if (it->second->hostname == arguments.at(0))
			{
				*user << Version(it->second->hostname, it->second->version);
				return (true);
			}
			++it;
		} */

		// No match ?
		*user << NoSuchServerError(arguments.at(0));
		return (false);
	}
}
