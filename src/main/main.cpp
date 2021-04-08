#include <irc/Server.hpp>
#include <csignal>

static void	doNothing(int)
{ std::cout << std::endl; }

static void	printUsage(std::string const& name)
{
	std::cerr << "Usage: "
		<< name << " [host:port_network:password_network] <port> <password>"
		<< std::endl;
}

int			main(int ac, char const *av[])
{
	irc::ServerConfig	config;

	try
	{ config = irc::ServerConfig(ac, av); }
	catch (std::invalid_argument const& e)
	{ std::cerr << "Invalid argument: " << e.what() << std::endl; printUsage(av[0]); return 1; };

	irc::Server			server(config);
	int					err = 0;

	signal(SIGINT, &doNothing);

	try { server.start(); }
	catch (SocketException const& e)
	{ std::cerr << e.what() << ": " << e.why() << std::endl; err = 2; }
	catch (...)
	{ std::cerr << "Unexpected exception!"; err = 3; }

	// std::cout << "Current config:" << std::endl << config;

	return err;
}
