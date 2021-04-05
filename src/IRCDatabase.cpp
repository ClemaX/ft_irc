#include <IRCDatabase.hpp>

namespace irc
{
	IRCDatabase::IRCDatabase()
		:	dataServersMap(), dataChannelsMap(), dataClientsMap(), modeFunctionsMap()
	{}

	IRCDatabase::IRCDatabase(Server* server)
		:	dataServersMap(), dataChannelsMap(), dataClientsMap(), modeFunctionsMap()
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


// --- Mode pointer functions --- //

	void	IRCDatabase::createModeFunctionsMap()
	{
		modeFunctionsMap['+'] = getPlusMap();
		modeFunctionsMap['-'] = getMinusMap();
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getPlusMap()
	{
		signedFunctionPointerMap	signedMap;
		signedMap['o'] = &addChannelOperator;
		signedMap['p'] = &setChannelPrivate;
		signedMap['s'] = &setChannelSecret;
		signedMap['i'] = &setChannelInviteOnly;
		signedMap['t'] = &setChannelRestrictTopic;
		signedMap['n'] = &setChannelNoExternalMessage;
		signedMap['m'] = &setChannelModerated;
		signedMap['l'] = &setChannelLimit;
		signedMap['b'] = &addChannelBanned;
		signedMap['v'] = &addChannelVoice;

		return signedMap;
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getMinusMap()
	{
		signedFunctionPointerMap	signedMap;
		signedMap['o'] = &removeChannelOperator;
		signedMap['p'] = &unsetChannelPrivate;
		signedMap['s'] = &unsetChannelSecret;
		signedMap['i'] = &unsetChannelInviteOnly;
		signedMap['t'] = &unsetChannelRestrictTopic;
		signedMap['n'] = &unsetChannelNoExternalMessage;
		signedMap['m'] = &unsetChannelModerated;
		signedMap['l'] = &unsetChannelLimit;
		signedMap['b'] = &removeChannelBanned;
		signedMap['v'] = &removeChannelVoice;

		return signedMap;
	}
}
