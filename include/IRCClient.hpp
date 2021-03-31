#pragma once

#include <string>

#include <ircdef.hpp>

#include <SocketConnection.hpp>

#include <IRCIReply.hpp>

namespace irc
{
	/**
	* In addition to the nickname, all servers must have the
	* following information about all clients: the real name of the host
	* that the client is running on, the username of the client on that
	* host, and the server to which the client is connected.
	*/
	class	Client	:	public SocketConnection
	{
	private:

	public:
		std::string	readBuffer;
		std::string	writeBuffer; // TODO: Should we use a Message container instead?

		std::string	nickname;
		std::string	hostname;
		std::string	username;
		std::string	server;

		Client(int fd, address const& address);

		Client const&	operator<<(IReply const* reply);
		Client const&	operator<<(std::string const& str);

		void	flush() throw(SocketWriteException);

		virtual ~Client() throw();
	};
}
