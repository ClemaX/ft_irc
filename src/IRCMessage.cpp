#include <IRCMessage.hpp>

namespace irc
{
	Message::Prefix::Prefix()
	{ }

	Message::Prefix::Prefix(std::string::const_iterator& it,
		std::string::const_iterator last) throw(InvalidMessageException)
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

	Message::Message(std::string& buffer) throw(MessageException)
	{
		static const unsigned		suffixLength = sizeof(IRC_MESSAGE_SUFFIX) - 1;
		static const unsigned		maxLength = IRC_MESSAGE_MAXLEN - suffixLength;
		size_t						newLength;
		std::string::const_iterator	it;
		std::string::const_iterator	end;
		std::string					argument;

		// Check message size
		newLength = buffer.find(IRC_MESSAGE_SUFFIX, 0, suffixLength);
		if (newLength == std::string::npos)
		{
			if (buffer.length() > maxLength)
				throw InvalidMessageException();
			throw IncompleteMessageException();
		}
		if (newLength > maxLength)
			throw InvalidMessageException();

		// Check and strip message suffix
		argument.assign(buffer, 0, newLength);
		buffer.erase(0, newLength + suffixLength);

		// Initialize iterators
		it = argument.begin();
		end = argument.end();

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
