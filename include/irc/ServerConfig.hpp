#pragma once

#include <string> // using std::string, std::strcmp
#include <map> // using std::map
#include <istream> // using std::istream, std::peek, std::skipws, std::getline
#include <fstream> // using std::ifstream
#include <algorithm> // using std::find

#define IRC_CONF_NAME		"ircserv.conf"
#define IRC_CONF_DELIM		'='
#define IRC_CONF_SEP		';'
#define IRC_CONF_NL			'\n'
#define IRC_CONF_NETHOST	"NETHOST"
#define IRC_CONF_NETPASS 	"NETPASS"
#define IRC_CONF_NETPORT 	"NETPORT"
#define IRC_CONF_HOSTNAME 	"HOSTNAME"
#define IRC_CONF_PORT 		"PORT"
#define IRC_CONF_PASS 		"PASS"
#define IRC_CONF_MOTD 		"MOTD"

namespace irc
{
	struct	ServerConfig
	{
		std::map<std::string, std::string>	data;

		void	serializeEntry(std::string& buffer, const char* key,
			std::string const& value) const throw();

		void	loadEntry(std::string const& key, std::string const& value)
			throw(std::out_of_range);

	public:
		static unsigned char const	argOptStart;
		static unsigned char const	argOptEnd;
		static unsigned char const	argReqStart;
		static unsigned char const	argReqEnd;

		static char const*			keys[];

		ServerConfig();
		virtual ~ServerConfig();

		ServerConfig(std::istream &is) throw(std::out_of_range);
		ServerConfig(std::string const& filepath) throw(std::out_of_range);
		ServerConfig(int ac, char const* av[]) throw(std::invalid_argument, std::out_of_range);

		bool	loadNetworkString(std::string const& network)
			throw(std::invalid_argument);

		std::istream&	operator>>(std::istream& is) throw(std::out_of_range);

		inline std::string&	operator[](std::string const& key)
			throw(std::out_of_range)
		{
			unsigned char	i;

			for (i = 0; keys[i] && keys[i] != key; i++);

			if (!keys[i])
				throw std::out_of_range(key);

			return data[key];
		}

		inline std::string	operator[](std::string const& key) const
			throw(std::out_of_range)
		{
			std::map<std::string, std::string>::const_iterator	it;
			unsigned char										i;

			for (i = 0; keys[i] && keys[i] != key; i++);

			if (!keys[i])
				throw std::out_of_range(key);

			it = data.find(key);
			if (it == data.end())
				return "";
			return it->second;
		}
	};

	std::ostream&	operator<<(std::ostream& os, ServerConfig const& config);
}
