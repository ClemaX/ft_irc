#include <irc/commands/ClientCommands.hpp>

#include <irc/replies/CommandReplies.hpp>
#include <irc/replies/ErrorReplies.hpp>

namespace
{
	std::string
	getLocalTime()
	throw()
	{
		// Thursday May 20 2021 -- 19:36:00 +00:00

		time_t now = time(NULL);
		// TODO: Use another timezone gien in arguments
		tm* const curr_time = localtime(&now);
		return (
			ft::itoa(curr_time->tm_mon + 1) + "/"
			+ ft::itoa(curr_time->tm_mday) + "/"
			+ ft::itoa(curr_time->tm_year + 1900) + " -- "
			+ ft::itoa(curr_time->tm_hour) + ":"
			+ ft::itoa(curr_time->tm_min) + ":"
			+ ft::itoa(curr_time->tm_sec) + " "
			+ curr_time->tm_zone
		);
	}
}

namespace NAMESPACE_IRC
{
	bool
	TimeCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		// No given args, use client's database
		if (arguments.empty())
		{
			*user << Time(database.hostname, getLocalTime());
			return (true);
		}

		// Given args, search the database and output it version
		Database::serverMap::const_iterator it = database.servers.begin();

		while (it != database.servers.end())
		{
			if (it->second->name == arguments.at(0))
			{
				// TODO: Handle server timezone
				// TODO: Check if we should use server name or hostname
				*user << Time(it->second->name, getLocalTime());
				return (true);
			}
			++it;
		}

		// No match ?
		*user << NoSuchServerError(arguments.at(0));
		return (false);
	}
}
