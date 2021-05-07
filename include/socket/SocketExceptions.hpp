#pragma once

#include <exception> // using std::exception

#include <cstring> // using strerror

class	SocketException	:	public std::exception
{
protected:
	const int	err;
	char const*	errMeaning;

public:
	SocketException(int err)
		:	err(err), errMeaning(strerror(err))
	{ }

	SocketException(int err, char const* errMeaning)
		:	err(err), errMeaning(errMeaning)
	{ }

	char const*	why() const throw()
	{ return  errMeaning; }
};

class	SocketOpenException	:	public SocketException
{
public:
	SocketOpenException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not open socket"; };
};

class	SocketCloseException	:	public SocketException
{
public:
	SocketCloseException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not close socket"; };
};

class	SocketOptionException	:	public SocketException
{
public:
	SocketOptionException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not set socket option"; }
};

class	SocketBindException	:	public SocketException
{
public:
	SocketBindException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not bind socket"; }
};

class	SocketListenException	:	public SocketException
{
public:
	SocketListenException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not listen on socket"; }
};

class	SocketSelectException	:	public SocketException
{
public:
	SocketSelectException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not select socket connections"; }
};

class	SocketAcceptException	:	public SocketException
{
public:
	SocketAcceptException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not accept socket connection"; }
};

class	SocketReadException	:	public SocketException
{
public:
	SocketReadException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not read from socket"; }
};

class	SocketWriteException	:	public SocketException
{
public:
	SocketWriteException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not write to socket"; }
};
