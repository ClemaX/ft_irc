# include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	namespace
	{
		bool
		show_server_connextions(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_hubs(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_client_connextions(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_banned(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_connextions_data(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_commands(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_host_operators(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_config(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}

		bool
		show_server_running_time(Server& server, Client* const user)
		{
			static_cast<void>(server);
			static_cast<void>(user);
			return (true);
		}
	}

	bool
	Server::StatsCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.empty())
		{
			// No args
		}

		Server* target_server = &server;

		if (arguments.size() > 1)
		{
			Server::serversMap::const_iterator it = server.database.dataServersMap.begin();

			while (it != server.database.dataServersMap.end())
			{
				if (it->second->hostname == arguments.at(1))
					target_server = it->second;
				++it;
			}

			if (target_server == &server)
			{
				// Error bad server name
			}
		}

		static const char* const queries[] = {
			"c", "h", "i", "k", "l", "m", "o", "y", "u"
		};

		static bool (*const handlers[])(Server&, Client* const) = {
			&show_server_connextions,
			&show_server_hubs,
			&show_client_connextions,
			&show_server_banned,
			&show_server_connextions_data,
			&show_server_commands,
			&show_server_host_operators,
			&show_server_config,
			&show_server_running_time
		};

		for (size_t i = ARRAY_SIZE(queries); --i ;)
			if (arguments.at(0) == queries[i])
				return (handlers[i](*target_server, user));

		// No querie no match
		return (false);
	}
}
