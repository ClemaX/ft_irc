#include <parseField.hpp>

namespace irc
{
	std::string::const_iterator	parseField(std::string& str,
		std::string::const_iterator first, std::string::const_iterator last)
	{
		while (*first == IRC_MESSAGE_DELIM)
			first++;
		if (first == last)
			return first;
		std::string::const_iterator	fieldLast =
			std::find(first, last, IRC_MESSAGE_DELIM);
		if (fieldLast == first)
			fieldLast = last;
		str.assign(first, fieldLast);
		return fieldLast;
	}
}
