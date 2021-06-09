#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::NoticeCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			// TODO: *user << NoRecipientError(gHostname, "PRIVMSG");
		}
		else if (arguments.size() == 1)
		{
			// TODO: *user << NoTextToSendError(gHostname);
		}
		else
		{
			std::string nameArgument = arguments[0];

			std::string message = "";
			if (arguments.size() > 1)
				message = arguments[1];

			AClient *receiver = server.database.getClient(nameArgument);
			if (receiver)
				receiver->receiveNotice(user, message);
			else
			{
				Server::__Channel *channel = server.database.getChannel(nameArgument);
				if (channel)
					channel->receiveNotice(user, message);
				// else
				// 	TODO: *user << NoSuchNicknameError(gHostname, nameArgument);
			}
		}
	}
}
