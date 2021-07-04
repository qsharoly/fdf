NAME = libft.a
SONAME = libft.so
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
SRCDIR = .
INCDIR = includes
OBJDIR = objects
DEPDIR = deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

ifeq ($(debug), yes)
	CCFLAGS += -g
endif
ifeq ($(optimize), yes)
	CCFLAGS += -O3
endif

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
	$(CC) --shared $(OBJ) -o $(SONAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d
	$(CC) -fpic $(DEPFLAGS) $(CCFLAGS) -c -o $@ $< -I $(INCDIR)

$(DEPDIR)/%d: ;

clean:
	rm -rf $(OBJDIR) $(DEPDIR)
fclean: clean
	rm -f $(NAME) $(SONAME)
re: fclean
	make all

-include $(DEPS)
