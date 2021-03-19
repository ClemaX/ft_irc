#include <IRCServer.hpp>
#include <csignal>

static void	doNothing(int)
{ }

int			main(void)
{
	irc::IRCServer		server;
	int					err = 0;

	signal(SIGINT, doNothing);

	try { server.start(); }
	catch (irc::SocketException const& e)
	{ std::cerr << e.what() << ": " << e.why() << std::endl; err = 1; }

	return err;
}
