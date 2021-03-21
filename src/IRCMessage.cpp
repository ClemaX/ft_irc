#include <IRCMessage.hpp>

namespace irc
{
	IRCMessage::Prefix::Prefix()
	{ }

	IRCMessage::Prefix::Prefix(std::string::const_iterator& it,
		std::string::const_iterator last)
	{
		std::string::const_iterator	needle;

		needle = std::find(it, last, IRC_MESSAGE_PREFIX_USER_PREFIX);
		if (needle != it)
		{
			it = parseField(user, ++needle, last);
			if (user.length() == 0)
				throw InvalidMessageException();
		}
		needle = std::find(it, last, IRC_MESSAGE_PREFIX_HOST_PREFIX);
		if (needle != it)
		{
			it = parseField(host, ++needle, last);
			if (host.length() == 0)
				throw InvalidMessageException();
		}
	}

	IRCMessage::IRCMessage(std::string const& message)
	{
		if (message.length() > IRC_MESSAGE_MAXLEN)
			throw InvalidMessageException();

		std::string::const_iterator			it = message.begin();
		std::string::const_iterator	const	end = message.end();

		if (*it == IRC_MESSAGE_PREFIX_PREFIX)
			prefix = Prefix(++it, end);
		if (it == end)
			throw;

		command = parseCommand(it, end);

		while (it != end)
		{
			std::string	argument;
			it = parseField(argument, it, end);
			arguments.push_back(argument);
		}
	}
}
