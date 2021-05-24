#include <irc/Server.hpp>

namespace NAMESPACE_IRC
{
	bool
	Server::TopicCommand::
	payload(Server& server, AClient* const user, argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
		{
			*user <<  NeedMoreParamsError(gHostname, name);
			return false;
		}

		const std::string channelName = ft::strToLower(arguments[0]);
		Server::__Channel	*channel = user->getChannel(channelName);

		if (!channel)
			*user <<  NotOnChannelError(gHostname, channelName);
		else if (arguments.size() == 1)
		{
			const std::string	topic = channel->getTopic();
			if (!topic.compare(""))
				*user << NoTopicReply(gHostname, channelName);
			else
				*user << TopicReply(gHostname, channelName, topic);
		}
		else if (!channel->isOperator(user))
			*user << ChannelOperatorPrivilegiesError(gHostname, channelName);
		else
		{
			const std::string newTopic = arguments[1];
			channel->setTopic(newTopic);
			*user << TopicReply(gHostname, channelName, newTopic);
		}
		return true;
	}
}
