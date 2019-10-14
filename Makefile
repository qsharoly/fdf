NAME = fdf
LFT_DIR = libft
LFT_INC = $(LFT_DIR)/includes
LFT = $(LFT_DIR)/libft.a
MLX_DIR = MinilibX
MLX_INC = $(MLX_DIR)/X11
MLX = $(MLX_DIR)/libmlx.a
INCDIR = includes
OBJDIR = objs
DEPDIR = deps

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
WFLAGS = -Wall -Wextra -Werror

SRC = main.c read_grid.c assign_colors_from_z.c ft_fmax.c ft_fmin.c\
	  bitmap.c make_rgba.c make_rect.c draw.c vector2.c vector3.c\
	  rotations.c projection.c make_float3.c hud.c keyboard.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEPS = $(SRC:%.c=$(DEPDIR)/%.d)

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LFT)
	gcc -o $(NAME) $(OBJ) -L $(MLX_DIR)  -L $(LFT_DIR)\
		-I $(MLX_INC) -I $(LFT_INC) -I $(INCDIR)\
		-I /files/usr/include\
		-landroid-shmem -lmlx -lft -lm -lX11 -lXext

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	gcc $(DEPFLAGS) $(WFLAGS) -g -c -o $@ $< -I $(MLX_INC) -I $(LFT_INC) -I $(INCDIR)

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
re: fclean
	make all

-include $(DEPS)
