#pragma once

#include <socket/SocketConnection.hpp>
#include <irc/ABufferedConnection.hpp>

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
		{ };

		virtual ~SocketClient() throw()
		{ }

		// TODO: Implement hopcount
		bool	isLocal() const throw()
		{ return true; }
/*
		void	close()
		{ operator<<("TODO: QUIT"); Socket::close(); } */
	};
}
