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

		typedef bool	(*ptr_function)(Client *user, Channel *channel, std::string & flagArguments);
		typedef	std::map<char, ptr_function>	signedFunctionPointerMap;
		typedef	std::map<char, signedFunctionPointerMap>	functionPointerMap;
		
		databaseServersMap	dataServersMap;
		databaseChannelsMap	dataChannelsMap;
		databaseClientsMap	dataClientsMap;

		functionPointerMap	modeFunctionsMap;


		IRCDatabase();
		IRCDatabase(Server* server);
		virtual ~IRCDatabase() throw();

		void	addServer(Server *server);
		void	addChannel(Channel *channel);
		void	addClient(Client *client);

	// --- Mode pointer functions --- //
		void	createModeFunctionsMap();
		signedFunctionPointerMap	getPlusMap();
		signedFunctionPointerMap	getMinusMap();
	};

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments);
	bool	setChannelNonPrivate(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments);
	bool	setChannelNonSecret(Client *user, Channel *channel, std::string & flagArguments);
}
