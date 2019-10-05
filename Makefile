NAME = fdf
LFT_DIR = libft
LFT = $(LFT_DIR)/libft.a
LFT_INC = $(LFT_DIR)/includes
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a

WFLAGS = -Wall -Wextra -Werror
SRC = main.c read_grid.c grid_z_range.c ft_fmax.c ft_fmin.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	gcc -o $(NAME) $(OBJ) -L $(MLX_DIR) -L $(LFT_DIR) -I $(MLX_DIR) -I $(LFT_INC) -lmlx -lft -framework OpenGL -framework AppKit

%.o: %.c
	gcc $(WFLAGS) -g -c -o $@ $< -I $(MLX_DIR) -I $(LFT_INC)

$(MLX):
	make -C $(MLX_DIR)

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean
	make all
