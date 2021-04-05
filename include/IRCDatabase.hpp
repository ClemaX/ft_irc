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

	bool	addChannelOperator(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelOperator(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelLimit(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelLimit(Client *user, Channel *channel, std::string & flagArguments);

	bool	addChannelBanned(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelBanned(Client *user, Channel *channel, std::string & flagArguments);

	bool	addChannelVoice(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelVoice(Client *user, Channel *channel, std::string & flagArguments);

	bool	addChannelKey(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelKey(Client *user, Channel *channel, std::string & flagArguments);
}
