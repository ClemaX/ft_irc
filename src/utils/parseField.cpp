#include <utils/parseField.hpp>

namespace irc
{

	int ft_toupper(int c)
	{
		if (c >= 'a' && c <= 'z')
			return c +'A' - 'a';
		return c;
	}

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
		{
			fieldLast = last;
			first++;				// removes ':' from the argument
		}
		else
			fieldLast =	std::find(first, last, IRC_MESSAGE_DELIM);

		str.assign(first, fieldLast);

		std::transform(str.begin(), str.end(), str.begin(),
			ft_toupper);

		// Lamba f is > c++98 [](unsigned char c){}

		return fieldLast;
	}

	std::string	mergeArguments(std::vector<std::string> arguments, size_t	begin_index)
	{
		std::string mergedArgument;

		if (begin_index < arguments.size())
			mergedArgument.assign(arguments[begin_index]);
		for (size_t i = begin_index + 1; i < arguments.size() ; i++)
		{
			mergedArgument.append(" ");
			mergedArgument.append(arguments[i]);
		}
		return mergedArgument;
	}

}
