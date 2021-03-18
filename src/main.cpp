#include <SocketServer.hpp>

int	main(void)
{
	irc::SocketServer	server;
	int					err = 0;

	try { server.start(); }
	catch (irc::SocketException const& e)
	{ std::cerr << e.what() << ": " << e.why() << std::endl; err = 1; }

	return err;
}
