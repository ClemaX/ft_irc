#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SOCKET_BUFFER_SIZE
# define SOCKET_BUFFER_SIZE	513U
#endif

typedef	sockaddr_in6		socketAddress;
typedef	struct in6_addr		internetAddress;
typedef	in_port_t			internetPort;
