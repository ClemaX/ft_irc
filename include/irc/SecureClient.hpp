#pragma once

#include <irc/Client.hpp>
#include <socket/SecureSocketConnection.hpp>

#include <socket/ssl.hpp>

namespace irc
{
	class	SecureClient
		:	public SecureSocketConnection, public Client
	{
	public:
		SecureClient(SSL* sslConnection, int fd,
			socketAddress const& address, bool authRequired);
	};
}
