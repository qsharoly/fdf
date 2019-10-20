NAME = fdf
LFT_DIR = libft
LFT_INC = $(LFT_DIR)/includes
LFT = $(LFT_DIR)/libft.a
MLX_DIR = minilibx_macos
MLX_INC = $(MLX_DIR)
MLX = $(MLX_DIR)/libmlx.a
INCDIR = includes
OBJDIR = objs
DEPDIR = deps

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
WFLAGS = -Wall -Wextra -Werror

SRC = main.c initialization.c read_grid.c assign_colors_from_z.c ft_fmax.c ft_fmin.c\
	  bitmap.c make_rect.c make_float3.c normalize.c draw.c draw_edge_gradient_z_buf.c\
	  draw_grid.c vector2.c vector3.c rotations.c projection.c hud.c keyboard.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEPS = $(SRC:%.c=$(DEPDIR)/%.d)

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LFT)
	gcc -o $(NAME) $(OBJ) -L $(MLX_DIR)  -L $(LFT_DIR)\
		-I $(MLX_INC) -I $(LFT_INC) -I $(INCDIR)\
		-lmlx -lft -framework OpenGL -framework AppKit

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	gcc $(DEPFLAGS) $(WFLAGS) -g -c -o $@ $< -I $(MLX_INC) -I $(LFT_INC) -I $(INCDIR)

$(DEPDIR)/%.d: ;

$(MLX):
	make -C $(MLX_DIR)

$(LFT):
	make -C $(LFT_DIR) debug

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
