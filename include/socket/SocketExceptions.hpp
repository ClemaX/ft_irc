#pragma once

#include <exception> // using std::exception

#include <cstring> // using strerror

#include <openssl/err.h>

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

	virtual char const*	why() const throw()
	{ return  errMeaning; }
};

class	SocketOpenException	:	public SocketException
{
public:
	SocketOpenException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not open socket"; };
};

class	SocketCloseException		:	public SocketException
{
public:
	SocketCloseException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not close socket"; };
};

class	SocketOptionException		:	public SocketException
{
public:
	SocketOptionException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not set socket option"; }
};

class	SocketBindException			:	public SocketException
{
public:
	SocketBindException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not bind socket"; }
};

class	SocketListenException		:	public SocketException
{
public:
	SocketListenException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not listen on socket"; }
};

class	SocketSelectException		:	public SocketException
{
public:
	SocketSelectException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not select socket connections"; }
};

class	SocketAcceptException		:	public SocketException
{
public:
	SocketAcceptException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not accept socket connection"; }
};

class	SocketReadException			:	public SocketException
{
public:
	SocketReadException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not read from socket"; }
};

class	SocketWriteException		:	public SocketException
{
public:
	SocketWriteException(int err)	:	SocketException(err) { }

	virtual char const*	what() const throw()
	{ return "Could not write to socket"; }
};

class	SSLException				:	public SocketException
{
public:
	SSLException(int err)			:	SocketException(err) { }

	virtual char const* why() const throw()
	{ return ERR_error_string(ERR_get_error(), NULL); }
};

class	SSLContextException			:	public SSLException
{
public:
	SSLContextException(int err)	:	SSLException(err) { }

	virtual char const* what() const throw()
	{ return "Could not create SSL context"; }
};

class	SSLCertException			:	public SSLContextException
{
public:
	SSLCertException(int err)		:	SSLContextException(err) { }

	virtual char const* what() const throw()
	{ return "Could not load SSL certificate"; }
};

class	SSLKeyException				:	public SSLContextException
{
public:
	SSLKeyException(int err)		:	SSLContextException(err) { }

	virtual char const* what() const throw()
	{ return "Could not load SSL key"; }
};

class	SSLAcceptException			:	public SSLException
{
public:
	SSLAcceptException(int err)		:	SSLException(err) { }

	virtual char const* what() const throw()
	{ return "Could not accept SSL connection"; }
};

class	SSLNewException				:	public SSLContextException
{
public:
	SSLNewException(int err)		:	SSLContextException(err) { }

	virtual char const* what() const throw()
	{ return "Could not create new SSL connection"; }
};
