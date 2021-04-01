#include <IRCDatabase.hpp>

namespace irc
{
	IRCDatabase::IRCDatabase()
		:	dataServersMap(), dataChannelsMap(), dataClientsMap()
	{}

	IRCDatabase::IRCDatabase(Server* server)
		:	dataServersMap(), dataChannelsMap(), dataClientsMap()
	{
		dataServersMap[server] = server;
	}	// Do we have to add the clients and channels of server ?

	IRCDatabase::~IRCDatabase() throw()
	{ }	// erase all three maps ?

	void	IRCDatabase::addServer(Server *server)
	{dataServersMap[server] = server;}

	void	IRCDatabase::addChannel(Channel *channel)
	{dataChannelsMap[channel->name] = channel;}

	void	IRCDatabase::addClient(Client *client)
	{dataClientsMap[client->username] = client;}		// use of username ?

}
