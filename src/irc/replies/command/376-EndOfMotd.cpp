#include <irc/replies/CommandReplies.hpp>

namespace NAMESPACE_IRC
{
// 376     IRC_RPL_ENDOFMOTD
//             ":End of /MOTD command"
	EndOfMotdReply::EndOfMotdReply(std::string const& serverName,
		std::string const& nickName)
		: NumericReply(serverName, IRC_RPL_ENDOFMOTD, nickName)
	{
		if (message.length())
			message.push_back(IRC_MESSAGE_DELIM);
		message << ":End of /MOTD command.";
	}
}
