NAME = fdf
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a
WFLAGS = -Wall -Wextra -Werror
SRC = main.c
OBJ = main.o

all: $(NAME)

$(NAME): $(OBJ) $(MLX)
	make -C $(MLX_DIR)
	gcc -o $(NAME) $(OBJ) -L $(MLX_DIR) -I $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

%.o: %.c
	gcc $(WFLAGS) -g -c -o $@ $< -I $(MLX_DIR)
