#include <irc/Server.hpp>

namespace irc
{
	Server::InviteCommand::InviteCommand()
		:	ChannelCommand("INVITE", true)
	{ }

	bool	Server::InviteCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (arguments.size() < 2)
		{
			*user <<  NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}
		std::string const nickname = arguments[0];
		std::string const channelName = arguments[1];

		Client *client = server.database.getClient(nickname);
		if (!client)
		{
			*user << NoSuchNicknameError(SERVER_NAME, nickname);
			return false;
		}
		Channel *channel = server.database.getChannel(channelName);
		if (!channel)
		{
			*user << InvitingReply(SERVER_NAME, channelName, nickname);
			*client << InviteChannelMessage(user->nickname, channelName);
		}
		else if (!user->isInChannel(channelName))
			*user << NotOnChannelError(SERVER_NAME, channelName);
		else if ((channel->channelModes.binMode & M_i) && !channel->isOperator(user))
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channelName);
		else if (client->isInChannel(channelName))
			*user << UserOnChannelError(SERVER_NAME, nickname, channelName);
		else
		{
			if (channel->channelModes.binMode & M_i)
				channel->addInviteList(nickname);
			*client << InviteChannelMessage(user->nickname, channelName);
			*user << InvitingReply(SERVER_NAME, channelName, nickname);
		}
		return true;
	}
}
