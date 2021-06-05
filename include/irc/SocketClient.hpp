#pragma once

#include <socket/SocketConnection.hpp>
#include <socket/ABufferedConnection.hpp>

#include <irc/AClient.hpp>

namespace irc
{
	class	SocketClient
		:	public virtual SocketConnection,
			public AClient
	{
	public:
		SocketClient(int fd, socketAddress const& address,
			bool authenticationRequired = false)
			:	SocketConnection(fd, address),
				AClient(authenticationRequired)
		{ Logger::instance() << Logger::DEBUG << "Constructing SocketClient on fd " << fd << std::endl; };

		virtual ~SocketClient() throw()
		{ Logger::instance() << Logger::DEBUG << "Destructing SocketClient on fd " << fd << std::endl; }
/*
		void	close()
		{ operator<<("TODO: QUIT"); Socket::close(); } */
	};
}
