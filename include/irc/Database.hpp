#pragma once

#include <map>
#include <irc/ircdef.hpp>
#include <utils/nickname.hpp>

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
		typedef ::std::map<std::string, Client*, nickcmp>	databaseClientsMap;

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

		Client	*getClient(std::string const &nickname) const;
		Channel	*getChannel(std::string const &channelName) const;

	// --- Mode pointer functions --- //
		void	createModeFunctionsMap();
		signedFunctionPointerMap	getPlusChannelMap();
		signedFunctionPointerMap	getMinusChannelMap();
		signedFunctionPointerMap	getPlusUserMap();
		signedFunctionPointerMap	getMinusUserMap();
	};

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
