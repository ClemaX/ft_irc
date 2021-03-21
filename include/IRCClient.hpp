#pragma once

#include <string>
#include <SocketServer.hpp>


namespace irc
{
	/**
	* In addition to the nickname, all servers must have the
	* following information about all clients: the real name of the host
	* that the client is running on, the username of the client on that
	* host, and the server to which the client is connected.
	*/
	struct	IRCClient	:	SocketConnection
	{
		std::string	nickname;
		std::string	hostname;
		std::string	username;
		std::string	server;

		IRCClient(struct sockaddr_in const& address);
	};
}