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
	{dataClientsMap[client->username] = client;}		// use of username ?


// --- Mode pointer functions --- //

	void	IRCDatabase::createModeFunctionsMap()
	{
		modeFunctionsMap['+'] = getPlusMap();
		modeFunctionsMap['-'] = getMinusMap();
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getPlusMap()
	{
		signedFunctionPointerMap	signedMap;
		signedMap['p'] = &setChannelPrivate;
		signedMap['s'] = &setChannelSecret;

		return signedMap;
	}

	IRCDatabase::signedFunctionPointerMap	IRCDatabase::getMinusMap()
	{
		signedFunctionPointerMap	signedMap;
		signedMap['p'] = &setChannelNonPrivate;
		signedMap['s'] = &setChannelNonSecret;

		return signedMap;
	}
}
