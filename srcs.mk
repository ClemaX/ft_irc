# Sources
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/,\
	$(addprefix irc/,\
		AMessage.cpp\
		Channel.cpp\
		Client.cpp\
		$(addprefix commands/,\
			Command.cpp\
			Commands.cpp\
			Commands_utils.cpp\
			Modes.cpp\
		)\
		Database.cpp\
		Message.cpp\
		PrivateMessage.cpp\
		$(addprefix replies/,\
			CommandReplies.cpp\
			ErrorReplies.cpp\
			NumericReplies.cpp\
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
		crypto.cpp\
		itoa.cpp\
		nickcmp.cpp\
		parseField.cpp\
	)\
)
