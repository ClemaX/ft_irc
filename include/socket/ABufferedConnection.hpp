#pragma once

#include <socket/IConnection.hpp>

#include <string>

class	ABufferedConnection	:	public virtual IConnection
{
protected:
	std::string	writeBuffer;

	ABufferedConnection()
	{ };

	virtual ~ABufferedConnection() throw()
	{ } // TODO: Maybe flush here

public:
	std::string	readBuffer;


	/// Add a message to the write buffer.
	/// The messages need to be flushed by calling flush().
	ABufferedConnection& operator<<(std::string const& message)
	{ writeBuffer += message; return *this; }

	/// Flushes the write buffer.
	void	flush()
	{
		write(writeBuffer.c_str(), writeBuffer.length());
		writeBuffer.clear();
	}
};
