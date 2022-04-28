NAME = libft.a
SONAME = libft.so
CL ?= clang
CCFLAGS = -Wall -Wextra -Werror
SRCDIR = .
INCDIR = includes
OBJDIR = objects
DEPDIR = deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

debug ?= -g
optimize ?= -O3

SRC = $(shell ls ft_*.c) get_next_line.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEPS = $(SRC:%.c=$(DEPDIR)/%.d)

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(OBJ)
	@echo --- link $(NAME) ---
	  ar rcs $(NAME) $(OBJ)

so: $(OBJ)
	$(CL) --shared $(OBJ) -o $(SONAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d
	$(CL) $(debug) $(optimize) $< -fpic $(DEPFLAGS) $(CCFLAGS) -I $(INCDIR) -c -o $@

$(DEPDIR)/%d: ;

clean:
	rm -rf $(OBJDIR) $(DEPDIR)
fclean: clean
	rm -f $(NAME) $(SONAME)
re: fclean
	make all

-include $(DEPS)
