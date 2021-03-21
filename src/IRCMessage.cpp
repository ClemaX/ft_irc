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

	IRCMessage::IRCMessage(std::string message)
	{
		// Check message size
		static const unsigned		suffixLength = sizeof(IRC_MESSAGE_SUFFIX) - 1;
		unsigned					newLength;
		std::string::const_iterator	it;
		std::string::const_iterator	end;
		std::string					argument;

		if (message.length() < suffixLength || message.length() > IRC_MESSAGE_MAXLEN)
			throw InvalidMessageException();

		newLength = message.length() - suffixLength;
		// Check and strip message suffix
		if (message.compare(newLength, suffixLength, IRC_MESSAGE_SUFFIX))
			throw InvalidMessageException();
		message.erase(newLength, suffixLength);

		// Initialize iterators
		it = message.begin();
		end = message.end();

		// Parse prefix
		if (*it == IRC_MESSAGE_PREFIX_PREFIX)
			prefix = Prefix(++it, end);
		if (it == end)
			throw InvalidMessageException();

		// Parse command
		command = parseCommand(it, end);

		// Parse arguments
		while (it != end)
		{
			it = parseField(argument, it, end);
			if (argument.length())
				arguments.push_back(argument);
		}
	}
}
