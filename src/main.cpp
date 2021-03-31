#include <IRCServer.hpp>
#include <csignal>

static void	doNothing(int)
{ std::cout << std::endl; }

int			main(void)
{
	SocketServer	server;
	int			err = 0;

	signal(SIGINT, &doNothing);

	try { server.start(); }
	catch (SocketException const& e)
	{ std::cerr << e.what() << ": " << e.why() << std::endl; err = 1; }

	return err;
}
