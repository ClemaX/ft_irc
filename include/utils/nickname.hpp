
#pragma once

#include <string>

namespace NAMESPACE_IRC
{
	bool    nicknameValidator(std::string const& nickname);

	struct nickcmp
	{
		struct nickcmpi
		{
			char    lower(char c) const
			{
				char    low;

				if (isupper(c))
					low = tolower(c);
				else if (c == '[')
					low = '{';
				else if (c == ']')
					low = '}';
				else if (c == '\\')
					low = '|';
				else
					low = c;

				return low;
			}

			bool operator()(unsigned char const& a, unsigned char const& b) const
			{ return (lower(a) < lower(b)); }
		};

		bool operator()(std::string const& a, std::string const& b) const
		{ return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), nickcmpi()); }
	};
}
