#include <utils/Logger.hpp>
#include <utils/strings.hpp>

#include <fstream>
#include <iomanip>

char const*const Logger::levelNames[] =
{
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR"
};

char const		Logger::levelFieldWidth = 7;

Logger::~Logger()
{ }

/*
Logger::Logger(std::ostream const& destination, Level minLevel)
	:	destination(destination), minLevel(minLevel)
{ }
 */

Logger::Logger(std::string const& filepath, Level minLevel)
	:	destination(filepath.c_str(), std::ios::app),
		nullStream(),
		minLevel(minLevel)
{ nullStream.setstate(std::ios::failbit); }

Logger& Logger::instance(std::string const& filepath, Level minLevel)
{
	static Logger	loggerInstance(filepath, minLevel);

	return loggerInstance;
}

void	Logger::log(std::string const& message, Level level)
{
	if (level >= minLevel)
		operator<<(level) << message << std::endl;
}

void	Logger::setFile(std::string const& filepath)
{
	destination.close();
	destination.clear();
	destination.open(filepath.c_str(), std::ios::app);
}

void	Logger::setLevel(Level level) throw()
{ minLevel = level; }

void	Logger::setLevel(std::string const& levelName)
	throw(std::domain_error)
{
	int	i = 0;

	while (i != _LAST && ft::strcmpi(levelNames[i], levelName.c_str()))
		i++;

	if (i == _LAST)
		throw std::domain_error(levelName);

	minLevel = static_cast<Level>(i);
}

std::ostream&	Logger::operator<<(Level level)
{
	if (level >= minLevel)
		return destination << std::left << std::setw(levelFieldWidth) << levelNames[level] << ' ';
	else
		return nullStream;
}

