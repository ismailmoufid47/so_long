NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I MLX42/include/MLX42 -I libft/include 
LFLAGS = -L MLX42/build -L /Users/isel-mou/.brew/opt/glfw/lib -L libft -l mlx42 -l glfw -l ft \
		 -framework Cocoa -framework OpenGL -framework IOKit

MLX = MLX42/build/libmlx42.a

SRC = so_long.c draw.c character.c walls_floors_and_move_count.c parse_map.c validate_map.c map_utils.c

SRC_BONUS = so_long_bonus.c exit_bonus.c enemy_bonus.c draw_bonus.c character.c walls_floors_and_move_count.c \
			parse_map.c validate_map.c map_utils.c

all: $(NAME)

$(NAME): $(MLX) libft/libft.a $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(NAME)

bonus: $(MLX) libft/libft.a $(SRC_BONUS)
	$(CC) $(CFLAGS) $(SRC_BONUS) $(LFLAGS) -o $(NAME)

$(MLX):
	make -C MLX42/build

libft/libft.a:
	make -C libft

clean:
	make -C libft clean
	make -C MLX42/build clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus