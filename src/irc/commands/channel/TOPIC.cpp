#include <irc/Server.hpp>

namespace irc
{
	Server::TopicCommand::TopicCommand()
		:	ChannelCommand("TOPIC", true)
	{ }

	bool	Server::TopicCommand::execute(Server& server, Client* user,
		argumentList const& arguments) const
	{
		(void)server;
		if (!arguments.size())
		{
			*user <<  NeedMoreParamsError(SERVER_NAME, name);
			return false;
		}

		const std::string channelName = ft::strToLower(arguments[0]);
		Channel	*channel = user->getChannel(channelName);

		if (!channel)
			*user <<  NotOnChannelError(SERVER_NAME, channelName);
		else if (arguments.size() == 1)
		{
			const std::string	topic = channel->getTopic();
			if (!topic.compare(""))
				*user << NoTopicReply(SERVER_NAME, channelName);
			else
				*user << TopicReply(SERVER_NAME, channelName, topic);
		}
		else if (!channel->isOperator(user))
			*user << ChannelOperatorPrivilegiesError(SERVER_NAME, channelName);
		else
		{
			const std::string newTopic = arguments[1];
			channel->setTopic(newTopic);
			*user << TopicReply(SERVER_NAME, channelName, newTopic);
		}
		return true;
	}
}
