#include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	namespace
	{
		inline void
		display_admin_data(const Database& database, AClient* const user)
		{
			*user << AdminMeReply(database.hostname, "database.admin.id.first");
			*user << AdminLoc1Reply(database.hostname, "database.admin.data1");
			*user << AdminLoc2Reply(database.hostname, "database.admin.data2");
			*user << AdminEmailReply(database.hostname, "database.admin.email");
		}
	}

	bool
	AdminCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
		{
			// TODO: Get the user's database or check if this is handled by relay
			display_admin_data(database, user);
			return (true);
		}
/*
		// Given args, search the database and output it version
		Database::serversMap::const_iterator it = database.dataServersMap.begin();

	 	while (it != database.dataServersMap.end())
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
