NAME = fdf
LFT_DIR = libft
LFT = $(LFT_DIR)/libft.a
LFT_INC = $(LFT_DIR)/includes
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a

WFLAGS = -Wall -Wextra -Werror
SRC = main.c read_grid.c
OBJ = main.o read_grid.o

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	make -C $(MLX_DIR)
	gcc -o $(NAME) $(OBJ) -L $(MLX_DIR) -L $(LFT_DIR) -I $(MLX_DIR) -I $(LFT_INC) -lmlx -lft -framework OpenGL -framework AppKit

%.o: %.c
	gcc $(WFLAGS) -g -c -o $@ $< -I $(MLX_DIR) -I $(LFT_INC)
