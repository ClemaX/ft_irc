#pragma once

#include <string> // using std::string
#include <list> // using std::list

#include <parseField.hpp>

#include <SocketServer.hpp>
#include <IRCChannel.hpp>
#include <IRCMessage.hpp>

// TODO: Grammar rules
// TODO: Handle nicknames containing {}| or []\ (as defined in RFC1459 2.2)
// TODO: Handle message prefix and reject invalid occurences (as defined in RFC1459 2.3)
// TODO: Handle message length including suffix
// TODO: See section 7?

namespace irc
{
	class	IRCServer	:	public SocketServer
	{
	protected:
		typedef ::std::map<std::string, std::list<IRCChannelClient*> >
			channelMap;

		channelMap	channels;

		virtual connection*	onConnection(int connectionFd,
			connectionAddress const& address);

		virtual void	onMessage(connection* connection,
			std::string const& message);

	public:
		IRCServer();
		~IRCServer();
	};
}



