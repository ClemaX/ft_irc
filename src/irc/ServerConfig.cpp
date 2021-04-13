#include <irc/ServerConfig.hpp>

	#include <iostream>

namespace irc
{
	unsigned char const	ServerConfig::argOptStart = 0;
	unsigned char const	ServerConfig::argOptEnd = 3;
	unsigned char const	ServerConfig::argReqStart = 3;
	unsigned char const	ServerConfig::argReqEnd = 5;

	char const* ServerConfig::keys[] = {
		IRC_CONF_HOST,
		IRC_CONF_NETPORT,
		IRC_CONF_NETPASS,
		IRC_CONF_PORT,
		IRC_CONF_PASS,
		IRC_CONF_MOTD,
		NULL
	};

	ServerConfig::ServerConfig()
	{ }

	ServerConfig::ServerConfig(std::istream &is)
	{ operator>>(is); }

	ServerConfig::ServerConfig(std::string const& filepath)
	{
		// std::ifstream	file(filepath);
		std::ifstream	file(filepath.c_str());

		operator>>(file);
		file.close();
	}

	bool	ServerConfig::loadNetworkString(std::string const& arg)
		throw(std::invalid_argument)
	{
		unsigned char						keyIndex = 0;
		std::string::const_iterator			it = arg.begin();
		std::string::const_iterator const	last = arg.end();
		std::string::const_iterator			next = std::find(it, last, ':');

		if (next == last)
			return false;

		for (; it != last && keyIndex != argOptEnd; keyIndex++)
		{
			operator[](keys[keyIndex]).assign(it, next);
			if (next != last)
				it = next + 1;
			else
				it = next;
			next = std::find(it, last, ':');
		}
		if (keyIndex != argOptEnd || it != last)
			throw std::invalid_argument(keys[keyIndex]);
		return true;
	}

	ServerConfig::ServerConfig(int ac, char const *av[])
		throw(std::invalid_argument)
	{
		int	i = 1;

		if (ac <= i)
		{
			// TODO: Try to load from /etc/ first
			std::ifstream	file(IRC_CONF_NAME);

			operator>>(file);
			file.close();
		}
		else
		{
			unsigned char	keyIndex = argReqStart;

			if (loadNetworkString(av[i]))
				i++;

			while (keyIndex < argReqEnd && i != ac)
			{
				operator[](keys[keyIndex]) = av[i];
				keyIndex++;
				i++;
			}

			if (keyIndex != argReqEnd || i != ac)
				throw std::invalid_argument(keys[keyIndex]);
		}
	}

	ServerConfig::~ServerConfig()
	{ }

	void	ServerConfig::serializeEntry(std::string& buffer, const char* key,
		std::string const& value) const throw()
	{
		buffer.append(key);
		buffer.push_back(IRC_CONF_DELIM);
		buffer.append(value);
		buffer.push_back(IRC_CONF_SEP);
		buffer.push_back(IRC_CONF_NL);
	}

	void	ServerConfig::loadEntry(std::string const& key,
		std::string const& value) throw(std::out_of_range)
	{
		unsigned char	i;

		for (i = 0; keys[i] && keys[i] != key; i++);

		if (!keys[i])
			throw std::out_of_range(key);

		data[key] = value;
	}

	std::istream&	ServerConfig::operator>>(std::istream& is) throw(std::out_of_range)
	{
		std::string	keyBuffer;
		std::string	valueBuffer;

		while (is.peek() != EOF)
		{
			std::getline(is >> std::ws, keyBuffer, IRC_CONF_DELIM);
			std::getline(is, valueBuffer, IRC_CONF_SEP);
			loadEntry(keyBuffer, valueBuffer);
		}

		return is;
	}

	std::ostream&	operator<<(std::ostream& os, ServerConfig const& config)
	{
		unsigned char i;

		for (i = 0; config.keys[i]; i++)
		{
			os << config.keys[i] << IRC_CONF_DELIM << config[config.keys[i]]
				<< IRC_CONF_SEP << IRC_CONF_NL;
		}

		return os;
	}
}
