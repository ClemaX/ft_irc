#include <irc/commands/ClientCommands.hpp>

namespace NAMESPACE_IRC
{
	bool
	NoticeCommand::
	payload(Database& database, AClient* const user, argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			// *user << NoRecipientError(gHostname, "PRIVMSG");
			return false;
		}
		if (arguments.size() == 1)
		{
			// *user << NoTextToSendError(gHostname);
			return false;
		}
		std::string nameArgument = arguments[0];

		std::string message = "";
		if (arguments.size() > 1)
			message = arguments[1];

		AClient *receiver = database.getClient(nameArgument);
		if (receiver)
			receiver->receiveMessage(user, message);
		else
		{
			Channel *channel = database.getChannel(nameArgument);
			if (channel)
				channel->receiveNotice(user, message);
			// else
			// 	*user << NoSuchNicknameError(gHostname, nameArgument);
		}
		return true;
	}
}
