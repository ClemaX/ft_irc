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
		typedef ::std::map<Server*, Server*>		serversMap;
		typedef ::std::map<std::string, Channel*>	channelsMap;
		typedef ::std::map<std::string, Client*>	clientsMap;


	public:
		serversMap	dataServersMap;
		channelsMap	dataChannelsMap;
		clientsMap	dataClientsMap;

		IRCDatabase();
		IRCDatabase(Server* server);
		virtual ~IRCDatabase() throw();

		void	addServer(Server *server);
		void	addChannel(Channel *channel);
		void	addClient(Client *client);
	};
}
