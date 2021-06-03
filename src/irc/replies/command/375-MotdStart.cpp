#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 375     IRC_RPL_MOTDSTART
//             ":- <server> Message of the day - "
	MotdStartReply::MotdStartReply(std::string const& serverName, std::string const& nickName, std::string const& motd)
		throw(InvalidMessageException)
		: NumericReply(serverName, IRC_RPL_MOTDSTART, nickName)
	{
		if (motd.length() > 80)
			throw (InvalidMessageException());

		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message << ":- " << serverName << " " << motd << " -";
	}
}
