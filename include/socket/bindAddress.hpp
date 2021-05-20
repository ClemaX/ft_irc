#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

int	bindAddress(std::string const &hostname, std::string const& port,
	int socketType, int socketOptions, int socketProtocol);
