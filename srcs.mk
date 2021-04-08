# Sources
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/,\
	$(addprefix irc/,\
		AMessage.cpp\
		Channel.cpp\
		Client.cpp\
		Command.cpp\
		Commands.cpp\
		Database.cpp\
		Message.cpp\
		Modes.cpp\
		Replies.cpp\
		Server.cpp\
		ServerConfig.cpp\
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
