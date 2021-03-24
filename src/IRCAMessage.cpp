#include <IRCAMessage.hpp>

namespace irc
{
	AMessage::Prefix::Prefix()
	{ }

	AMessage::Prefix::Prefix(std::string const& name,
		std::string const& user, std::string const host)
		:	name(name),
			user(user),
			host(host)
	{ }

	AMessage::Prefix::Prefix(std::string::const_iterator& it,
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

	std::string	AMessage::Prefix::serialize() const throw()
	{
		std::string	serialized;

		if (!isEmpty())
		{
			serialized.push_back(IRC_MESSAGE_PREFIX_PREFIX);
			serialized.append(name);

			if (user.length())
			{
				serialized.push_back(IRC_MESSAGE_PREFIX_USER_PREFIX);
				serialized.append(user);
			}

			if (host.length())
			{
				serialized.push_back(IRC_MESSAGE_PREFIX_HOST_PREFIX);
				serialized.append(host);
			}
		}

		return serialized;
	}
}
