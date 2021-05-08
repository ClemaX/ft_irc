#include <irc/Server.hpp>
#include <csignal>

namespace
{
	bool	running = true;

	void	restart(int)
	{ running = true; }

	void	doNothing(int)
	{ std::cout << std::endl; }

	void	printUsage(std::string const& name)
	{
		std::cerr << "Usage: "
			<< name << " [host:port_network:password_network] <port> <password>"
			<< std::endl;
	}
}

int			main(int ac, char const *av[])
{
	int					err = 0;
	irc::ServerConfig	config;

	while (running)
	{
		running = false;

		try
		{ config = irc::ServerConfig(ac, av); }
		catch (std::invalid_argument const& e)
		{ std::cerr << "Invalid argument: " << e.what() << std::endl; printUsage(av[0]); err = 1; break; }
		catch (std::out_of_range const& e)
		{ std::cerr << "Invalid config key: " << e.what() << std::endl; err = 2; break; }
		catch (...)
		{ std::cerr << "Unexpected exception!"; err = 3; break; };

		irc::Server			server(config);

		signal(SIGHUP, &restart);
		signal(SIGINT, &doNothing);
		signal(SIGTERM, &doNothing);

		try { server.start(); }
		catch (SocketException const& e)
		{ std::cerr << e.what() << ": " << e.why() << std::endl; err = 2; }
		catch (...)
		{ std::cerr << "Unexpected exception!" << std::endl; err = 3; }
	}

	// std::cout << "Current config:" << std::endl << config;

	return err;
}
