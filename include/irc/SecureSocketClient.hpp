#pragma once

#include <irc/SocketClient.hpp>
#include <socket/SecureSocketConnection.hpp>

#include <socket/ssl.hpp>

namespace irc
{
	class	SecureSocketClient
		:	public SecureSocketConnection, public SocketClient
	{
	public:
		SecureSocketClient(SSL* sslConnection, int fd,
			socketAddress const& address, bool authRequired);

		bool	isLocal() const throw()
		{ return true; }
	};
}
