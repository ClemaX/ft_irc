#pragma once

#include <string>
#include <algorithm>
#include <vector>

#include <irc/ircdef.hpp>

namespace irc
{
	std::string::const_iterator	parseField(std::string& str,
			std::string::const_iterator first, std::string::const_iterator last);

	std::string	mergeArguments(std::vector<std::string>, size_t	begin_index);
}
