# Sources
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/,\
	$(addprefix irc/,\
		AMessage.cpp\
		PrivateMessage.cpp\
		Channel.cpp\
		Client.cpp\
		Database.cpp\
		Message.cpp\
		Server.cpp\
		ServerConfig.cpp\
		$(addprefix replies/,\
			NumericReplies.cpp\
			CommandReplies.cpp\
			ErrorReplies.cpp\
		)\
		$(addprefix commands/,\
			Command.cpp\
			Commands.cpp\
			Modes.cpp\
		)\
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
		crypto.cpp\
		itoa.cpp\
		parseField.cpp\
	)\
)
