#pragma once

#include <string>
#include <queue>

namespace irc
{
	void	parseArgumentsQueue(std::string const &argument, std::queue<std::string> &argQueue);
	bool	matchPattern_multiple(std::string const &str, std::string const &pattern);
	bool	matchPattern_unique(std::string const &str, std::string const &pattern);
	bool	matchPattern_global(std::string const &str, std::string const &pattern);
}
