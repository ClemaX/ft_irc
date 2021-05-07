#include <irc/replies/NumericReplies.hpp>
#include <irc/Client.hpp>

namespace irc
{
	NumericReply::NumericReply(std::string const& serverName,
		int code, std::string const& message)
		:	prefix(serverName),
			code(code),
			message(message)
	{ }

	NumericReply::~NumericReply()
	{ }

	std::string	NumericReply::serialize() const throw()
	{
		std::string	serialized;

		serialized.append(prefix.serialize());
		serialized.push_back(IRC_MESSAGE_DELIM);
		serialized.append(ft::itoa(code));
		serialized.push_back(IRC_MESSAGE_DELIM);
		serialized.append(message);
		serialized.append(IRC_MESSAGE_SUFFIX);

		return serialized;
	}
}
