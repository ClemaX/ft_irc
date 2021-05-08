#include <irc/replies/CommandReplies.hpp>

namespace irc
{
// 372     IRC_RPL_MOTD
//             ":- <text>"
	MotdReply::MotdReply(std::string const& serverName,
		std::string const& nickName, std::string const& motd)
		throw(InvalidMessageException)
		: NumericReply(serverName, IRC_RPL_MOTD, nickName)
	{
		if (motd.length() > 80)
			throw (InvalidMessageException()); // TODO: Maybe use another (Reply-)exception type
		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message << ":- " << motd << " -";
	}
}
