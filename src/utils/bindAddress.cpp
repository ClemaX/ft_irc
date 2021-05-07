#include <utils/bindAddress.hpp>

#include <socket/SocketExceptions.hpp>

#include <fcntl.h>

#include <algorithm>
#include <iostream>

class SocketAddressException: public SocketException
{
public:
	SocketAddressException(int err)
		:	SocketException(err, gai_strerror(err))
	{ }
};

int	bindAddress(std::string const &hostname, std::string const& port,
	int socketType, int socketOptions, int socketProtocol)
{
	int				err;
	int				fd;
	struct addrinfo	hints;
	struct addrinfo	*info;
	struct addrinfo	*curr;


	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = socketType;
	hints.ai_protocol = socketProtocol;
	//hints.ai_flags = AI_V4MAPPED | AI_ALL;

	err = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &info);
	if (err)
		throw SocketAddressException(err);

	for (curr = info; curr != NULL; curr = curr->ai_next)
	{

		if (curr->ai_socktype & socketType)
		{
			fd = socket(curr->ai_family, curr->ai_socktype | socketOptions,
				curr->ai_protocol);
			if (fd != -1 && bind(fd, curr->ai_addr, curr->ai_addrlen) == 0)
				break;
			else
				close(fd);
		}
	}

	freeaddrinfo(info);

	if (curr == NULL)
		throw SocketBindException(errno != 0 ? errno : EADDRNOTAVAIL);

	return fd;
}
