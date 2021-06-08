#pragma once

#include <socket/IConnection.hpp>

#include <string>

#include <utils/Logger.hpp>

class	ABufferedConnection	:	public virtual IConnection
{
protected:
	std::string	writeBuffer;

	ABufferedConnection()
	{ Logger::instance() << Logger::DEBUG << "Constructing ABufferedConnection..." << std::endl; };

	virtual ~ABufferedConnection() throw()
	{ Logger::instance() << Logger::DEBUG << "Destroying ABufferedConnection..." << std::endl; } // TODO: Maybe flush here

public:
	std::string	readBuffer;

	/// Add a message to the write buffer.
	/// The messages need to be flushed by calling flush().
	ABufferedConnection& operator<<(std::string const& message)
	{ writeBuffer += message; return *this; }

	/// Flushes the write buffer.
	void	flush()
	{
		if (write(writeBuffer.c_str(), writeBuffer.length()))
			writeBuffer.clear();
	}
};
