#include <irc/ServerConfig.hpp>
#include <iostream>
#include <irc/ircdef.hpp>

namespace NAMESPACE_IRC
{
	unsigned char const	ServerConfig::argOptStart = 0;
	unsigned char const	ServerConfig::argOptEnd = 3;
	unsigned char const	ServerConfig::argReqStart = 3;
	unsigned char const	ServerConfig::argReqEnd = 5;

	ServerConfig::Field const	ServerConfig::fields[] = {
		{IRC_CONF_NETHOST, ""},
		{IRC_CONF_NETPORT, ""},
		{IRC_CONF_NETPASS, ""},
		{IRC_CONF_PORT, "6666"},
		{IRC_CONF_PASS, ""},
		{IRC_CONF_MOTD, "Hello world!"},
		{IRC_CONF_HOSTNAME, "localhost"},
		{IRC_CONF_SSLPORT, ""},
		{IRC_CONF_SSLCERT, ""},
		{IRC_CONF_SSLKEY, ""},
		{IRC_CONF_LOGFILE, "/dev/stderr"},
		{IRC_CONF_LOGLEVEL, "INFO"}
	};

	unsigned char const	ServerConfig::fieldCount =
		sizeof(fields) / sizeof(*fields);

	ServerConfig::ServerConfig()
	{ }

	// TODO: Maybe implement copy constructor and assignment operator

	ServerConfig::ServerConfig(std::istream &is) throw(std::out_of_range)
	{ operator>>(is); }

	ServerConfig::ServerConfig(std::string const& filepath)
		throw(std::out_of_range)
	{
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
			operator[](fields[keyIndex].key).assign(it, next);
			if (next != last)
				it = next + 1;
			else
				it = next;
			next = std::find(it, last, ':');
		}
		if (keyIndex != argOptEnd || it != last)
			throw std::invalid_argument(fields[keyIndex].key);
		return true;
	}

	ServerConfig::ServerConfig(int ac, char const *av[])
		throw(std::invalid_argument, std::out_of_range)
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
				operator[](fields[keyIndex].key) = av[i];
				keyIndex++;
				i++;
			}

			if (keyIndex != argReqEnd || i != ac)
				throw std::invalid_argument(fields[keyIndex].key);
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

		for (i = 0; i != fieldCount && fields[i].key != key; i++);

		if (i == fieldCount)
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

		for (i = 0; i < config.fieldCount; i++)
		{
			os << config.fields[i].key << IRC_CONF_DELIM << config[config.fields[i].key]
				<< IRC_CONF_SEP << IRC_CONF_NL;
		}

		return os;
	}
}
