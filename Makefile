BIN ?= fdf
CL ?= clang
INCDIR = includes
OBJDIR = objs
DEPDIR = deps

LFT_DIR = libft
LFT_INC = $(LFT_DIR)/includes
LFT = $(LFT_DIR)/libft.a
LIB_FLAGS += -lft -lmlx

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_S), Linux)
	MLX_DIR = minilibx
	MLX_INC = $(MLX_DIR)/include
	LIB_FLAGS += -lm -lXext -lX11
ifeq ($(UNAME_M), aarch64)
	LIB_FLAGS += -landroid-shmem
endif
else
	MLX_DIR = minilibx_macos
	MLX_INC = $(MLX_DIR)
	LIB_FLAGS += -framework OpenGL -framework AppKit
endif
MLX = $(MLX_DIR)/libmlx.a

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
CCFLAGS += -Wall -Wextra -Werror
INC_PATHS = -I $(MLX_INC) -I $(LFT_INC) -I $(INCDIR)
LIB_PATHS += -L $(MLX_DIR) -L $(LFT_DIR)

debug ?= -gdwarf-4
optimize ?= -O2

export debug
export optimize
export CL

SRC = main.c\
	  init.c\
	  load_map.c\
	  color.c\
	  draw_line.c\
	  draw_map.c\
	  vector3.c\
	  hud.c\
	  keyboard.c\
	  mouse.c\
	  ft_mini_dtoa.c\
	  camera.c\
	  matrix.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEPS = $(SRC:%.c=$(DEPDIR)/%.d)

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

all: $(BIN)

$(BIN): $(OBJ) $(MLX) $(LFT)
	@echo "# linking $(BIN)"
	$(CL) -o $(BIN) $(OBJ)\
		$(LIB_PATHS)\
		$(INC_PATHS)\
		$(LIB_FLAGS)

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CL) $(debug) $(optimize) $< $(DEPFLAGS) $(CCFLAGS) $(INC_PATHS) -c -o $@

$(DEPDIR)/%.d: ;

$(MLX):
	make -C $(MLX_DIR)

$(LFT):
	make -C $(LFT_DIR) 

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJDIR) $(DEPDIR)
fclean: clean
	rm -rf $(BIN)
	make -C $(MLX_DIR) fclean
	make -C $(LFT_DIR) fclean
re: fclean
	make all

-include $(DEPS)
