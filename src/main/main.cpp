#include <irc/Server.hpp>
#include <csignal>

static void	doNothing(int)
{ std::cout << std::endl; }

int			main(void)
{
	irc::ServerConfig	config("ircserv.conf");
	irc::Server			server(config);
	int					err = 0;

	signal(SIGINT, &doNothing);

	try { server.start(); }
	catch (SocketException const& e)
	{ std::cerr << e.what() << ": " << e.why() << std::endl; err = 1; }

	// std::cout << "Current config:" << std::endl << config;

	return err;
}
