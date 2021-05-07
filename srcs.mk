# Sources
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/,\
	$(addprefix irc/,\
		AMessage.cpp\
		Channel.cpp\
		Client.cpp\
		Database.cpp\
		Message.cpp\
		Server.cpp\
		ServerConfig.cpp\
		$(addprefix commands/,\
			Command.cpp\
			Commands.cpp\
			Modes.cpp\
		)\
		$(addprefix replies/,\
			CommandReplies.cpp\
			ErrorReplies.cpp\
			NumericReplies.cpp\
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
		bindAddress.cpp\
		crypto.cpp\
		itoa.cpp\
		parseField.cpp\
	)\
)
