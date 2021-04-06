#include <IRCDatabase.hpp>

namespace irc
{
	IRCDatabase::IRCDatabase()
		:	dataServersMap(), dataChannelsMap(), dataClientsMap(),
			modeChannelFunctionsMap(), modeUserFunctionsMap()
	{}

	IRCDatabase::IRCDatabase(Server* server)
		:	dataServersMap(), dataChannelsMap(), dataClientsMap(),
			modeChannelFunctionsMap(), modeUserFunctionsMap()
	{
		dataServersMap[server] = server;
		createModeFunctionsMap();
	}	// Do we have to add the clients and channels of server ?

	IRCDatabase::~IRCDatabase() throw()
	{ }	// erase all three maps ?

	void	IRCDatabase::addServer(Server *server)
	{dataServersMap[server] = server;}

	void	IRCDatabase::addChannel(Channel *channel)
	{dataChannelsMap[channel->name] = channel;}

	void	IRCDatabase::addClient(Client *client)
	{dataClientsMap[client->nickname] = client;}		// use of nickname ?


// --- Channel Mode pointer functions --- //

	void	IRCDatabase::createModeFunctionsMap()
	{
		modeChannelFunctionsMap['+'] = getPlusChannelMap();
		modeChannelFunctionsMap['-'] = getMinusChannelMap();
		modeUserFunctionsMap['+'] = getPlusUserMap();
		modeUserFunctionsMap['-'] = getMinusUserMap();
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getPlusChannelMap()
	{
		signedFunctionPointerMap	signedMap;

		signedMap['O'] = &addChannelCreator;
		signedMap['o'] = &addChannelOperator;
		signedMap['v'] = &addChannelVoice;

		signedMap['a'] = &setChannelAnonymous;
		signedMap['i'] = &setChannelInviteOnly;
		signedMap['m'] = &setChannelModerated;
		signedMap['n'] = &setChannelNoExternalMessage;
		signedMap['q'] = &setChannelQuiet;
		signedMap['p'] = &setChannelPrivate;
		signedMap['s'] = &setChannelSecret;
		signedMap['r'] = &setChannelReop;
		signedMap['t'] = &setChannelRestrictTopic;
		
		signedMap['l'] = &setChannelLimit;
		signedMap['k'] = &addChannelKey;
		
		signedMap['b'] = &addChannelBanned;
		signedMap['e'] = &addChannelException;
		signedMap['I'] = &addChannelInviteList;

		return signedMap;
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getMinusChannelMap()
	{
		signedFunctionPointerMap	signedMap;

		signedMap['o'] = &removeChannelOperator;
		signedMap['v'] = &removeChannelVoice;

		signedMap['a'] = &unsetChannelAnonymous;
		signedMap['i'] = &unsetChannelInviteOnly;
		signedMap['m'] = &unsetChannelModerated;
		signedMap['n'] = &unsetChannelNoExternalMessage;
		signedMap['q'] = &unsetChannelQuiet;
		signedMap['p'] = &unsetChannelPrivate;
		signedMap['s'] = &unsetChannelSecret;
		signedMap['r'] = &unsetChannelReop;
		signedMap['t'] = &unsetChannelRestrictTopic;
		
		signedMap['l'] = &unsetChannelLimit;
		signedMap['k'] = &removeChannelKey;
		
		signedMap['b'] = &removeChannelBanned;
		signedMap['e'] = &removeChannelException;
		signedMap['I'] = &removeChannelInviteList;

		return signedMap;
	}


// --- User Mode pointer functions --- //

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getPlusUserMap()
	{
		signedFunctionPointerMap	signedMap;

		signedMap['i'] = &setUserInvisible;
		signedMap['s'] = &setUserServerNotice;
		signedMap['w'] = &setUserWallops;
		signedMap['o'] = &setUserOperator;	// can a server use this function to set an operator ?

		return signedMap;
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getMinusUserMap()
	{
		signedFunctionPointerMap	signedMap;

		signedMap['i'] = &unsetUserInvisible;
		signedMap['s'] = &unsetUserServerNotice;
		signedMap['w'] = &unsetUserWallops;
		signedMap['o'] = &unsetUserOperator;

		return signedMap;
	}
}
