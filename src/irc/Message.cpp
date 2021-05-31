#include <irc/Message.hpp>

#include <utils/strings.hpp>

namespace NAMESPACE_IRC
{
	template<typename _Cmd>
	_Cmd const*	parseCommand(
		_Cmd const*const commands[],
		size_t commandCount,
		std::string::const_iterator& it, std::string::const_iterator& last)
	{
		std::string	name;
		unsigned	i = 0;

		it = parseField(name, it, last);

		if (name.length() == 0)
			return NULL;

		while (i < commandCount
			&& ft::strcmpi(name.c_str(), commands[i]->name.c_str()))
			i++;
		if (i == commandCount)
			return NULL;

		return commands[i];
	}

	template<typename _Cmd>
	Message<_Cmd>::Message(_Cmd const*const commands[], size_t commandCount, std::string& buffer) throw(MessageException)
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
		command = parseCommand(commands, commandCount, it, end);

		// str_arguments.copy(argument);
		// Parse arguments
		while (it != end)
		{
			it = parseField(argument, it, end);
			if (argument.length())
				arguments.push_back(argument);
		}
	}
}
