#pragma once

#include <string>

#include <IRCServer.hpp>
#include <IRCClient.hpp>
#include <IRCChannel.hpp>

namespace irc
{
	class Server;
	class Client;
	class Channel;

	class	IRCDatabase
	{
	private:

	public:
		typedef ::std::map<Server*, Server*>		databaseServersMap;
		typedef ::std::map<std::string, Channel*>	databaseChannelsMap;
		typedef ::std::map<std::string, Client*>	databaseClientsMap;
		
		databaseServersMap	dataServersMap;
		databaseChannelsMap	dataChannelsMap;
		databaseClientsMap	dataClientsMap;

		IRCDatabase();
		IRCDatabase(Server* server);
		virtual ~IRCDatabase() throw();

		void	addServer(Server *server);
		void	addChannel(Channel *channel);
		void	addClient(Client *client);
	};
}
