NAME = ircserv

# Compiler and linker
CXX = clang++
LD = clang++

# Paths
SRCDIR = src
SRC_SUBDIRS = "" IRC main socket utils
INCDIR = include/
LIBDIR = ..

OBJDIR = obj/
BINDIR = .

# Library dependencies
LIBS = $(addprefix $(LIBDIR)/, )

INCDIRS = $(addprefix $(INCDIR), $(SRC_SUBDIRS))

LIBDIRS = $(dir $(LIBS))
LIBINCS = $(addsuffix $(INCDIR), $(LIBDIRS))
LIBARS = $(notdir $(LIBS))

# Include directories
SYSINCS = /usr/include /usr/local/include

ifeq ($(shell find -L $(SYSINCS) -maxdepth 1 -type d -name openssl -print -quit 2>/dev/null), )
	BREW = $(shell dirname $(dir $(shell which brew)))

	ifneq ($(BREW), )
		USRINC = $(shell find -L $(BREW)/include -maxdepth 1 -type d -name openssl -print -quit)
		USRLIB = $(shell find -L $(BREW)/lib -maxdepth 1 -type f -iname "libssl*" -print -quit)
	endif

	ifeq ($(USRINC), )
$(error Could not find OpenSSL headers!)
	endif

	ifeq ($(USRLIB), )
$(error Could not find OpenSSL library!)
	endif

	LIBINCS += $(dir $(USRINC))
	LIBDIRS += $(dir $(USRLIB))
endif

INCS = $(LIBINCS) $(INCDIRS)

# Sources
PRE_SRCS = IRC/IRCAMessage\
	IRC/IRCChannel\
	IRC/IRCCommand\
	IRC/IRCCommands\
	IRC/IRCClient\
	IRC/IRCDatabase\
	IRC/IRCMessage\
	IRC/IRCModes\
	IRC/IRCReplies\
	IRC/IRCServer\
	IRC/IRCServerConfig\
	main/main\
	socket/SocketConnection\
	socket/SocketServer\
	utils/atoi\
	utils/crypto\
	utils/itoa\
	utils/parseField\


# OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS = $(addsuffix .o, $(addprefix $(OBJDIR), $(PRE_SRCS)))

DEPS = $(OBJS:.o=.d)

# Flags
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -Wno-c++11-long-long $(INCS:%=-I%) -g3
DFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)$*.d
LDFLAGS = $(LIBDIRS:%=-L%)
LDLIBS = $(LIBARS:lib%.a=-l%) -lcrypto

# Compiling commands
COMPILE.cpp = $(CXX) $(DFLAGS) $(CXXFLAGS) -c
COMPILE.o = $(LD) $(LDFLAGS)

all: $(BINDIR)/$(NAME)
	./$(NAME)

# Directories
$(OBJDIR) $(BINDIR):
	@echo "MK $@"
	mkdir -p "$@"

# Libraries
$(LIBS): %.a: FORCE
	make -C $(dir $@) NAME=$(@F)

# Objects
$(OBJS): $(OBJDIR)%.o: $(SRCDIR)/%.cpp $(OBJDIR)%.d | $(OBJDIR)
	@mkdir -p '$(@D)'
	@echo "CXX $<"
	$(COMPILE.cpp) $< -o $@

# Dependencies
$(DEPS): $(OBJDIR)%.d:
include $(wildcard $(DEPS))

# Binaries
$(BINDIR)/$(NAME): $(OBJS) $(LIBS) | $(BINDIR)
	@echo "LD $@ $(LIBARS:lib%.a=-l%)"
	$(COMPILE.o) $(OBJS) -o $@ $(LDLIBS)

# Remove temporary objects
clean:
	# $(foreach libdir, $(LIBDIRS),\
		echo "MK -C $(libdir) $@" && make -C $(libdir) $@ && ):
	@echo "RM $(OBJDIR)"
	rm -rf "$(OBJDIR)"

# Remove all binaries
fclean: clean
	# $(foreach libdir, $(LIBDIRS),\
	# 	echo "MK -C $(libdir) $@" && make -C $(libdir) $@ && ):
	@echo "RM $(BINDIR)/$(NAME)"
	rm -f "$(BINDIR)/$(NAME)"
	@rmdir "$(BINDIR)" 2>/dev/null && echo "RM $(BINDIR)" || :

# Remove and rebuild all binaries
re: fclean all

FORCE: ;

.PHONY: all clean fclean re

# Assign a value to VERBOSE to enable verbose output
$(VERBOSE).SILENT:
