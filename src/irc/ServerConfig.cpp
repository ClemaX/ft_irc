#include <irc/ServerConfig.hpp>

namespace irc
{
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
		std::ifstream	file(filepath);

		operator>>(file);
		file.close();
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
