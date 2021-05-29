#pragma once

#include <unistd.h>

class IConnection
{
private:

public:
	IConnection() throw() { };
	virtual ~IConnection() throw() { };

	//virtual void	close() = 0;

	virtual bool	read(char* buffer, size_t n) = 0;
	virtual bool	write(char const* buffer, size_t n) const = 0;
};
