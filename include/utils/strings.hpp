#pragma once

#include <cstddef>
#include <string>

namespace ft
{
	inline void			bzero(void *s, size_t n)
	{
		char *temp = static_cast<char*>(s);

		while (n--)
			*temp++ = 0;
	}

	inline std::string	strToLower(const std::string & str)
	{
		std::string	lowStr(str);
		for(std::string::iterator it = lowStr.begin() ; it != lowStr.end() ; it++)
			if (*it >= 'A' && *it <= 'Z')
				*it = *it - 'A' + 'a';
		return lowStr;
	}

	inline int			strcmpi(char const* a, char const* b)
	{
		while (*a && std::tolower(*a) == std::tolower(*b))
		{
			a++;
			b++;
		}
		return (std::tolower(*b) - std::tolower(*a));
	}
}
