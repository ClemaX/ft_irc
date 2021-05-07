#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#ifndef SOCKET_BUFFER_SIZE
# define SOCKET_BUFFER_SIZE	513U
#endif

typedef	sockaddr_in6	socketAddress;
typedef	in6_addr_t		internetAddress;
typedef	in_port_t		internetPort;
