#include <irc/Server.hpp>
#include <irc/PrivateMessage.hpp>

namespace NAMESPACE_IRC
{
	void
	Server::InviteCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		if (arguments.size() < 2)
			*user <<  NeedMoreParamsError(gHostname, name);
		else
		{
			std::string const nickname = arguments[0];
			std::string const channelName = arguments[1];

			AClient *client = server.database.getClient(nickname);
			if (!client)
				*user << NoSuchNicknameError(gHostname, nickname);
			else
			{
				__Channel *channel = server.database.getChannel(channelName);
				if (!channel)
				{
					*user << InvitingReply(gHostname, channelName, nickname);
					*client << InviteChannelMessage(server.hostname, user->nickname, channelName);
				}
				else if (!user->isInChannel(channelName))
					*user << NotOnChannelError(gHostname, channelName);
				else if ((channel->channelModes & __Channel::i) && !channel->isOperator(user))
					*user << ChannelOperatorPrivilegiesError(gHostname, channelName);
				else if (client->isInChannel(channelName))
					*user << UserOnChannelError(gHostname, nickname, channelName);
				else
				{
					if (channel->channelModes & __Channel::i)
						channel->addInviteList(user->nickname, nickname);
					*client << InviteChannelMessage(user->nickname, channelName, nickname);
					// *user << InvitingReply(gHostname, channelName, nickname);
					*user << InviteChannelMessage(user->nickname, channelName, nickname);
				}
			}
		}
	}
}
