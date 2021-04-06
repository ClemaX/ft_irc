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

		functionPointerMap	modeChannelFunctionsMap;
		functionPointerMap	modeUserFunctionsMap;


		IRCDatabase();
		IRCDatabase(Server* server);
		virtual ~IRCDatabase() throw();

		void	addServer(Server *server);
		void	addChannel(Channel *channel);
		void	addClient(Client *client);

	// --- Mode pointer functions --- //
		void	createModeFunctionsMap();
		signedFunctionPointerMap	getPlusChannelMap();
		signedFunctionPointerMap	getMinusChannelMap();
		signedFunctionPointerMap	getPlusUserMap();
		signedFunctionPointerMap	getMinusUserMap();
	};


// Channel modes
	bool	addChannelCreator(Client *user, Channel *channel, std::string & flagArguments);
	
	bool	addChannelOperator(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelOperator(Client *user, Channel *channel, std::string & flagArguments);

	bool	addChannelVoice(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelVoice(Client *user, Channel *channel, std::string & flagArguments);


	bool	setChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelAnonymous(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelInviteOnly(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelModerated(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelModerated(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelNoExternalMessage(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelQuiet(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelQuiet(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelPrivate(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelPrivate(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelSecret(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelSecret(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelReop(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelReop(Client *user, Channel *channel, std::string & flagArguments);

	bool	setChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelRestrictTopic(Client *user, Channel *channel, std::string & flagArguments);


	bool	setChannelLimit(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetChannelLimit(Client *user, Channel *channel, std::string & flagArguments);

	bool	addChannelKey(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelKey(Client *user, Channel *channel, std::string & flagArguments);


	bool	addChannelBanned(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelBanned(Client *user, Channel *channel, std::string & flagArguments);
	
	bool	addChannelException(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelException(Client *user, Channel *channel, std::string & flagArguments);
	
	bool	addChannelInviteList(Client *user, Channel *channel, std::string & flagArguments);
	bool	removeChannelInviteList(Client *user, Channel *channel, std::string & flagArguments);

// User modes
	bool	setUserInvisible(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserInvisible(Client *user, Channel *channel, std::string & flagArguments);

	bool	setUserServerNotice(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserServerNotice(Client *user, Channel *channel, std::string & flagArguments);

	bool	setUserWallops(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserWallops(Client *user, Channel *channel, std::string & flagArguments);

	bool	setUserOperator(Client *user, Channel *channel, std::string & flagArguments);
	bool	unsetUserOperator(Client *user, Channel *channel, std::string & flagArguments);

}
