#include <irc/Server.hpp>

namespace irc
{
	Server::InviteCommand::InviteCommand()
		:	ChannelCommand("INVITE", true)
	{ }

	bool	Server::InviteCommand::payload(Server& server, Client* user,
		argumentList const& arguments) const
	{
		if (arguments.size() < 2)
		{
			*user <<  NeedMoreParamsError(gHostname, name);
			return false;
		}
		std::string const nickname = arguments[0];
		std::string const channelName = arguments[1];

		Client *client = server.database.getClient(nickname);
		if (!client)
		{
			*user << NoSuchNicknameError(gHostname, nickname);
			return false;
		}
		Channel *channel = server.database.getChannel(channelName);
		if (!channel)
		{
			*user << InvitingReply(gHostname, channelName, nickname);
			*client << InviteChannelMessage(user->nickname, channelName);
		}
		else if (!user->isInChannel(channelName))
			*user << NotOnChannelError(gHostname, channelName);
		else if ((channel->channelModes.binMode & M_i) && !channel->isOperator(user))
			*user << ChannelOperatorPrivilegiesError(gHostname, channelName);
		else if (client->isInChannel(channelName))
			*user << UserOnChannelError(gHostname, nickname, channelName);
		else
		{
			if (channel->channelModes.binMode & M_i)
				channel->addInviteList(nickname);
			*client << InviteChannelMessage(user->nickname, channelName);
			*user << InvitingReply(gHostname, channelName, nickname);
		}
		return true;
	}
}
