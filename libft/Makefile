NAME = libft.a
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
SRCDIR = .
INCDIR = includes
OBJDIR = objects
DEPDIR = deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

SRC = $(shell ls ft_*.c) get_next_line.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEPS = $(SRC:%.c=$(DEPDIR)/%.d)

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

.PHONY: all debug clean fclean re
all: $(NAME)

debug: CCFLAGS += -g
debug: $(NAME)

$(NAME): $(OBJ)
	@echo --- link ---
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d
	$(CC) $(DEPFLAGS) $(CCFLAGS) -c -o $@ $< -I $(INCDIR)

$(DEPDIR)/%d: ;

clean:
	rm -rf $(OBJDIR) $(DEPDIR)
fclean: clean
	rm -f $(NAME)
re: fclean
	make all

-include $(DEPS)
