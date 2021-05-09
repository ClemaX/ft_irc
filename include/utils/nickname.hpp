
#pragma once

#include <string>

namespace irc
{
	namespace
	{
		char    lower(char c)
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

		bool    nicknameCmp(std::string const& a, std::string const& b)
		{
			std::string::const_iterator const    endA = a.end();
			std::string::const_iterator            itA = a.begin();
			std::string::const_iterator            itB = b.begin();

			while (itA != endA && lower(*itA) == lower(*itB))

			{
				itA++;
				itB++;
			}
			return lower(*itA) - lower(*itB);
		}
	}

	bool    nicknameValidator(std::string const& nickname);

	struct nickcmp
	{
		bool operator()(std::string const& a, std::string const& b) const
		{ return (nicknameCmp(a, b)); }
	};

}
