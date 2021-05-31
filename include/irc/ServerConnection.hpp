#pragma once

#include <irc/AServerConnection.hpp>

namespace irc
{
	class	ServerConnection
		:	public virtual SocketConnection,
			public AServerConnection
	{

	};
}
