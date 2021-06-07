NAME = ircserv

# Compiler and linker
CXX = clang++
LD = clang++

# Paths
include srcs.mk

INCDIR = include
LIBDIR = ..

OBJDIR = obj

# Library dependencies
LIBS = $(addprefix $(LIBDIR)/, )

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



INCS = $(LIBINCS) $(INCDIR)

OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
#OBJS = $(addsuffix .o, $(addprefix $(OBJDIR), $(PRE_SRCS)))

DEPS = $(OBJS:.o=.d)

# Flags
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -Wno-c++11-long-long $(INCS:%=-I%) -g3
DFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.d
LDFLAGS = $(LIBDIRS:%=-L%) -g3
LDLIBS = $(LIBARS:lib%.a=-l%) -lssl -lcrypto

# Compiling commands
COMPILE.cpp = $(CXX) $(DFLAGS) $(CXXFLAGS) -c
COMPILE.o = $(LD) $(DFLAGS) $(LDFLAGS)

all: $(NAME)

# Directories
$(OBJDIR) $(BINDIR):
	@echo "MK $@"
	mkdir -p "$@"

# Libraries
$(LIBS): %.a: FORCE
	make -C $(dir $@) NAME=$(@F)

# Objects
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(OBJDIR)/%.d | $(OBJDIR)
	@mkdir -p '$(@D)'
	@echo "CXX $<"
	$(COMPILE.cpp) $< -o $@

# Dependencies
$(DEPS): $(OBJDIR)%.d:
-include $(wildcard $(DEPS))

# Binaries
$(NAME): $(OBJS) $(LIBS) | $(BINDIR)
	@echo "LD $@ $(LIBARS:lib%.a=-l%)"
	$(COMPILE.o) $(OBJS) -o $@ $(LDLIBS)
	$(openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes -subj "/CN=localhost")

# Remove temporary objects
clean:
	# $(foreach libdir, $(LIBDIRS), echo "MK -C $(libdir) $@" && make -C $(libdir) $@ && ):
	@echo "RM $(OBJDIR)"
	rm -rf "$(OBJDIR)"

# Remove all binaries
fclean: clean
	# $(foreach libdir, $(LIBDIRS),\ echo "MK -C $(libdir) $@" && make -C $(libdir) $@ && ):
	@echo "RM $(NAME)"
	rm -f "$(NAME)"

# Remove and rebuild all binaries
re: fclean all

run: $(BINDIR)/$(NAME)
	./$(NAME)

FORCE: ;

.PHONY: all clean fclean re

# Assign a value to VERBOSE to enable verbose output
$(VERBOSE).SILENT:
