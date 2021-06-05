#pragma once

#include <irc/SocketClient.hpp>
#include <socket/SecureSocketConnection.hpp>

#include <socket/ssl.hpp>

namespace irc
{
	class	SecureSocketClient
		:	public virtual SecureSocketConnection, public AClient
	{
	public:
		SecureSocketClient(SSL* sslConnection, int fd,
			socketAddress const& address, bool authRequired);
	};
}
