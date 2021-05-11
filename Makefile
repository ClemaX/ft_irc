NAME = ircserv

# Compiler and linker
CXX = clang++
LD = clang++

# Paths
include srcs.mk

INCDIR = include
LIBDIR = ..

OBJDIR = obj

# Include directories
INCS = $(LIBINCS) $(INCDIR)

OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

DEPS = $(OBJS:.o=.d)

# Flags
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -Wno-c++11-long-long $(INCS:%=-I%)
DFLAGS = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.d

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
	$(COMPILE.o) $(OBJS) -o $@

# Remove temporary objects
clean:
	@echo "RM $(OBJDIR)"
	rm -rf "$(OBJDIR)"

# Remove all binaries
fclean: clean
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
