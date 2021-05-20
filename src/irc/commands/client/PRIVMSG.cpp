#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::PRIVMSGCommand::
	payload(Server& server, Client* const user, argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NoRecipientError(gHostname, "PRIVMSG");
			return false;
		}
		if (arguments.size() == 1)
		{
			*user << NoTextToSendError(gHostname);
			return false;
		}
		std::string nameArgument = arguments[0];

		std::string message = "";
		if (arguments.size() > 1)
			message = arguments[1];

		Client *receiver = server.database.getClient(nameArgument);
		if (receiver)
			receiver->receiveMessage(user, message);
		else
		{
			Server::__Channel *channel = server.getChannel(nameArgument);
			if (channel)
				channel->receiveMessage(user, message);
			else
				*user << NoSuchNicknameError(gHostname, nameArgument);
		}
		return true;
	}
}
