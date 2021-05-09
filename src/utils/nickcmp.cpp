
#include <utils/nickname.hpp>
#include <irc/ircdef.hpp>

namespace irc
{
	namespace
	{
		bool    isspecial(int c)
		{
			char const*    set = IRC_CHARSET_SPECIAL;

			while (*set != '\0' && *set != (char)c)
				set++;
			return *set != '\0';
		}
	}

	bool    nicknameValidator(std::string const& nickname)
	{
		std::string::const_iterator            it = nickname.begin();
		std::string::const_iterator const    end = nickname.end();

		if (nickname.length() > IRC_NICKNAME_MAXLEN || !isalpha(*it))
			return false;

		while (isalnum(*it) || isspecial(*it))
			it++;

		return it == end;
	}

}
