# Sources
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/,\
	$(addprefix irc/,\
		AMessage.cpp\
		Channel.cpp\
		ChannelModes.cpp\
		Client.cpp\
		Command.cpp\
		$(addprefix commands/,\
			$(addprefix channel/,\
				INVITE.cpp\
				JOIN.cpp\
				KICK.cpp\
				LIST.cpp\
				NAMES.cpp\
				PART.cpp\
				TOPIC.cpp\
			)\
			MODE.cpp\
			MOTD.cpp\
			NICK.cpp\
			NOTICE.cpp\
			PASS.cpp\
			PRIVMSG.cpp\
			USER.cpp\
			utils.cpp\
			WHO.cpp\
		)\
		Database.cpp\
		Message.cpp\
		PrivateMessage.cpp\
		$(addprefix replies/,\
			$(addprefix command/,\
				001-Welcome.cpp\
				002-YourHost.cpp\
				003-Created.cpp\
				004-MyInfo.cpp\
				005-Bounce.cpp\
				221-UModeIs.cpp\
				301-Away.cpp\
				302-UserHost.cpp\
				315-EndOfWho.cpp\
				322-List.cpp\
				323-ListEnd.cpp\
				324-ChannelModeIs.cpp\
				325-UniqOpIs.cpp\
				331-NoTopic.cpp\
				332-Topic.cpp\
				341-Inviting.cpp\
				346-InviteList.cpp\
				347-EndOfInviteList.cpp\
				348-ExceptionList.cpp\
				349-EndOfExceptionList.cpp\
				351-Who.cpp\
				353-Names.cpp\
				366-EndOfNames.cpp\
				367-BanList.cpp\
				368-EndOfBanList.cpp\
				372-Motd.cpp\
				375-MotdStart.cpp\
				376-EndOfMotd.cpp\
				TODO.cpp\
			)\
			$(addprefix error/,\
				401-NoSuchNick.cpp\
				402-NoSuchServer.cpp\
				403-NoSuchChannel.cpp\
				404-CannotSendToChan.cpp\
				405-TooManyChannels.cpp\
				407-TooManyTargets.cpp\
				411-NoRecipient.cpp\
				412-NoTextToSend.cpp\
				416-TooManyMatches.cpp\
				431-NoNicknameGiven.cpp\
				432-ErroneusNickname.cpp\
				433-NicknameInUse.cpp\
				436-NickCollisionReply.cpp\
				437-UnavailableResource.cpp\
				441-UserNotInChannel.cpp\
				442-NotOnChannel.cpp\
				443-UserOnChannel.cpp\
				451-ClientNotRegistered.cpp\
				461-NeedMoreParams.cpp\
				461-UserParams.cpp\
				462-UserAlreadyRegistred.cpp\
				471-ChannelIsFull.cpp\
				472-UnknownMode.cpp\
				473-InviteOnlyChannel.cpp\
				474-BannedFromChannel.cpp\
				475-BadChannelKey.cpp\
				476-BadChannelMask.cpp\
				477-NoChannelModes.cpp\
				482-ChannelOperatorPrivileges.cpp\
				501-UModeUnknownFlag.cpp\
				502-UsersDontMatch.cpp\
				TODO.cpp\
			)\
			NumericReply.cpp\
		)\
		ServerConfig.cpp\
		Server.cpp\
	)\
	$(addprefix main/,\
		main.cpp\
	)\
	$(addprefix socket/,\
		SocketConnection.cpp\
		SocketServer.cpp\
	)\
	$(addprefix utils/,\
		atoi.cpp\
		bindAddress.cpp\
		itoa.cpp\
		nickcmp.cpp\
		parseField.cpp\
	)\
)
