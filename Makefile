NAME = fdf
INCDIR = includes
OBJDIR = objs
DEPDIR = deps

LFT_DIR = libft
LFT_INC = $(LFT_DIR)/includes
LFT = $(LFT_DIR)/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR = minilibx
	MLX_INC = $(MLX_DIR)/include
	LIB_FLAGS += -lm -lXext -lX11
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
LIB_FLAGS += -lft -lmlx

debug = yes

ifeq ($(debug), yes)
	CCFLAGS += -g
endif

SRC = main.c\
	  startup.c\
	  load_map.c\
	  map_make_colors.c\
	  ft_fmax.c\
	  ft_fmin.c\
	  bitmap.c\
	  make_rect.c\
	  make_vec3.c\
	  normalize3.c\
	  draw.c\
	  draw_zbuf.c\
	  draw_map.c\
	  vector2.c\
	  vector3.c\
	  rotations.c\
	  projection.c\
	  hud.c\
	  keyboard.c\
	  ft_itoa_float.c\
	  ft_put_float.c\
	  cam_move.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEPS = $(SRC:%.c=$(DEPDIR)/%.d)

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LFT)
	@echo "# linking $(NAME)"
	gcc -o $(NAME) $(OBJ)\
		$(LIB_PATHS)\
		$(INC_PATHS)\
		$(LIB_FLAGS) $(MLX_DEPS)

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	gcc $(DEPFLAGS) $(CCFLAGS) -c -o $@ $< $(INC_PATHS) 

$(DEPDIR)/%.d: ;

$(MLX):
	make -C $(MLX_DIR)

$(LFT):
	make -C $(LFT_DIR) 

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJDIR) $(DEPDIR)
fclean: clean
	rm -rf $(NAME)
	make -C $(MLX_DIR) clean
	make -C $(LFT_DIR) fclean
re: fclean
	make all

-include $(DEPS)
