#include <irc/Server.hpp>
#include <csignal>
#include <socket/ssl.hpp>

#include <utils/Logger.hpp>

namespace
{
	bool	running = true;

	void	restart(int)
	{ running = true; }

	void	doNothing(int)
	{ std::cout << std::endl; }

	void	printUsage(std::string const& name, std::ostream& os = std::cerr)
	{
		os << "Usage: "
			<< name << " [host:port_network:password_network] <port> <password>"
			<< std::endl;
	}
}

int			main(int ac, char const *av[])
{
	Logger&				logger(Logger::instance());
	int					err(0);
	irc::ServerConfig	config;
	irc::Server			server;

	//logger << Logger::ERROR << "test" << std::endl;

	while (running)
	{
		running = false;

		try
		{ config = irc::ServerConfig(ac, av); }
		catch (std::invalid_argument const& e)
		{ std::cerr << "Invalid argument: " << e.what() << std::endl; printUsage(av[0]); err = 1; break; }
		catch (std::out_of_range const& e)
		{ std::cerr << "Invalid config key: " << e.what() << std::endl; err = 2; break; }
		catch (std::exception const& e)
		{ std::cerr << "Unexpected exception: " << e.what() << std::endl; err = 3; break; }
		catch (...)
		{ std::cerr << "Unexpected exception!"; err = 3; break; };

		try
		{
			logger.setFile(config[IRC_CONF_LOGFILE]);
			logger.setLevel(config[IRC_CONF_LOGLEVEL]);
		}
		catch (std::domain_error const& e)
		{ std::cerr << "Invalid minimal log-level: '" << e.what() << '\'' << std::endl; err = 4; break; }
		catch (std::exception const& e)
		{ std::cerr << "Unexpected exception: " << e.what() << std::endl; err = 3; break; }
		catch (...)
		{ std::cerr << "Unexpected exception!"; err = 3; break; };

		ssl::init();

		// TODO: catch BindException

		try
		{ server.loadConfig(config); }
		catch (SocketException const& e)
		{ logger << Logger::ERROR << e.what() << ": " << e.why() << std::endl; err = 5; break; }
		catch (std::exception const& e)
		{ logger << Logger::ERROR << "Unexpected exception: " << e.what() << std::endl; err = 3; break; }
		catch (...)
		{ logger << Logger::ERROR << "Unexpected exception!" << std::endl; err = 3; break; }

		signal(SIGHUP, &restart);
		signal(SIGINT, &doNothing);
		signal(SIGTERM, &doNothing);

		try { server.start(); }
		catch (SocketException const& e)
		{ logger << Logger::ERROR << e.what() << ": " << e.why() << std::endl; err = 5; break; }
		catch (std::exception const& e)
		{ logger << Logger::ERROR << "Unexpected exception: " << e.what() << std::endl; err = 3; break; }
		catch (...)
		{ logger << Logger::ERROR << "Unexpected exception!" << std::endl; err = 3; break; }

		ssl::cleanup();
	}

	// std::cout << "Current config:" << std::endl << config;

	return err;
}
