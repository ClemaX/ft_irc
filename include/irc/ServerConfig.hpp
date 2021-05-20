#pragma once

#include <string> // using std::string, std::strcmp
#include <map> // using std::map
#include <istream> // using std::istream, std::peek, std::skipws, std::getline
#include <fstream> // using std::ifstream
#include <algorithm> // using std::find

# include <irc/ircdef.hpp>

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
#define IRC_CONF_SSLPORT	"SSLPORT"
#define IRC_CONF_SSLCERT	"SSLCERT"
#define IRC_CONF_SSLKEY		"SSLKEY"
#define IRC_CONF_LOGFILE	"LOGFILE"
#define IRC_CONF_LOGLEVEL	"LOGLEVEL"

namespace NAMESPACE_IRC
{
	struct	ServerConfig
	{
	private:
		std::map<std::string, std::string>	data;

		void	serializeEntry(std::string& buffer, const char* key,
			std::string const& value) const throw();

		void	loadEntry(std::string const& key, std::string const& value)
			throw(std::out_of_range);

		static unsigned char const	argOptStart;
		static unsigned char const	argOptEnd;
		static unsigned char const	argReqStart;
		static unsigned char const	argReqEnd;

	public:
		struct	Field
		{
			std::string const	key;
			std::string const	defaultValue;
		};

		static Field const			fields[];

		static unsigned char const	fieldCount;

		ServerConfig();
		virtual ~ServerConfig();

		ServerConfig(std::istream &is) throw(std::out_of_range);
		ServerConfig(std::string const& filepath) throw(std::out_of_range);
		ServerConfig(int ac, char const* av[]) throw(std::invalid_argument, std::out_of_range);

		bool	loadNetworkString(std::string const& network)
			throw(std::invalid_argument);

		std::istream&	operator>>(std::istream& is) throw(std::out_of_range);

		std::string	operator[](std::string const& key) const
			throw(std::out_of_range)
		{
			std::map<std::string, std::string>::const_iterator	it;
			unsigned char										i;

			for (i = 0; i != fieldCount && fields[i].key != key; i++);

			if (i == fieldCount)
				throw std::out_of_range(key);

			it = data.find(key);
			if (it == data.end())
				return fields[i].defaultValue;
			return it->second;
		}
	};

	std::ostream&	operator<<(std::ostream& os, ServerConfig const& config);
}
