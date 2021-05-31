#pragma once

#include <socket/IConnection.hpp>

#include <irc/replies/IReply.hpp>

#include <string>

namespace irc
{

	class	ABufferedConnection	:	public virtual IConnection
	{
	protected:
		std::string	writeBuffer;

		ABufferedConnection(bool authenticationRequired)
			:	authenticated(!authenticationRequired)
		{ };

		virtual ~ABufferedConnection() throw()
		{ } // TODO: Maybe flush here

	public:
		// TODO: Encapsulate readBuffer
		std::string	readBuffer;

		bool	authenticated;

		/// Add a message to the write buffer.
		/// The messages need to be flushed by calling flush().
		ABufferedConnection& operator<<(std::string const& message)
		{ writeBuffer += message; return *this; }

		/// Serialize a message and add it to the write buffer.
		/// The messages need to be flushed by calling flush().
		ABufferedConnection&	operator<<(IReply const& message)
		{ operator<<(message.serialize()); return *this; };

		/// Flushes the write buffer.
		void	flush()
		{
			write(writeBuffer.c_str(), writeBuffer.length());
			writeBuffer.clear();
		}

		/// Has the connection been successfully identified
		virtual bool	isRegistered() const throw()
		{ return false; }

		// IRC netwide unique identifier
		virtual std::string	getUid() const throw()
		{ return IRC_NICKNAME_DEFAULT; }
	};
}
