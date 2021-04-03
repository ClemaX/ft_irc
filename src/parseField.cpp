#include <parseField.hpp>

namespace irc
{
	std::string::const_iterator	parseField(std::string& str,
		std::string::const_iterator first, std::string::const_iterator last)
	{
		while (*first == IRC_MESSAGE_DELIM)
			first++;

		if (first == last)
		{
			str.clear();
			return first;
		}

		std::string::const_iterator	fieldLast;
		if (*first == IRC_MESSAGE_PREFIX_PREFIX)
			fieldLast = last;
		else
			fieldLast =	std::find(first, last, IRC_MESSAGE_DELIM);

		str.assign(first, fieldLast);

		return fieldLast;
	}
}
