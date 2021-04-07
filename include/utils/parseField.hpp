#pragma once

#include <string>
#include <algorithm>

#include <ircdef.hpp>

namespace irc
{
	std::string::const_iterator	parseField(std::string& str,
	std::string::const_iterator first, std::string::const_iterator last);
}
