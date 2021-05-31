#pragma once

#include <irc/replies/IReply.hpp>
#include <irc/ABufferedConnection.hpp>


namespace irc
{
	class	AServerConnection	:	public ABufferedConnection
	{
	protected:
		AServerConnection(bool authRequired) throw()
			:	ABufferedConnection(authRequired)
		{ }

	public:
		/// An unique name acting as the server's identifier.
		/// Only character from the message charset are allowed.
		/// Uniqueness is case-insensitive.
		std::string	name;

		AServerConnection&	operator<<(IReply const& message)
		{ ABufferedConnection::operator<<(message.serialize()); return *this; };
		AServerConnection&	operator<<(std::string const& message)
		{ ABufferedConnection::operator<<(message); return *this; }

		virtual ~AServerConnection() throw()
		{ }
	};
}
