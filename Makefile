NAME = fdf
LFT_DIR = libft
LFT = $(LFT_DIR)/libft.a
LFT_INC = $(LFT_DIR)/includes
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a
INC_DIR = includes

WFLAGS = -Wall -Wextra -Werror
SRC = main.c read_grid.c assign_colors_from_z.c ft_fmax.c ft_fmin.c\
	  bitmap.c make_rgba.c make_rect.c draw.c vector2.c vector3.c\
	  vector3_more.c rotations.c make_float3.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LFT)
	gcc -o $(NAME) $(OBJ) -L $(MLX_DIR) -L $(LFT_DIR)\
		-I $(MLX_DIR) -I $(LFT_INC) -I $(INC_DIR)\
		-lmlx -lft -framework OpenGL -framework AppKit

%.o: %.c $(INC_DIR)/fdf.h
	gcc $(WFLAGS) -g -c -o $@ $< -I $(MLX_DIR) -I $(LFT_INC) -I $(INC_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(LFT):
	make -C $(LFT_DIR)

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean
	make all
