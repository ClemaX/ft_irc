#include <irc/Server.hpp>

namespace irc
{
	Server::PRIVMSGCommand::PRIVMSGCommand()
		:	Command("MSG")
	{ }

	bool	Server::PRIVMSGCommand::payload(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (!arguments.size())
		{
			*user << NeedMoreParamsError(gHostname, name);
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
			Channel *channel = server.getChannel(nameArgument);
			if (channel)
				channel->receiveMessage(user, message);
		}
		return true;
	}
}
