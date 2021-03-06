#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

#include <socket/SocketExceptions.hpp>

int	bindAddress(std::string const &hostname, std::string const& port,
	int socketType, int socketOptions, int socketProtocol) throw(SocketAddressException, SocketBindException);
