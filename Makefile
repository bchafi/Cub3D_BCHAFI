CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = libft.a

LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*.c)

LIBFT_OBJ = $(wildcard $(LIBFT_DIR)/*.o)

LIBFT_DIR = libft

MLX42FLAGS_LINUX= libmlx42_linux.a -Iinclude -ldl -lglfw -pthread -lm
MLX42FLAGS_MAC= libmlx42_mac.a -Iinclude -L/goinfre/bchafi/homebrew/opt/glfw/lib -lglfw -fsanitize=address,undefined

RAYCAST = raycasting/utils.c raycasting/player.c  raycasting/init_actor_data.c raycasting/input.c  raycasting/ft_free.c raycasting/draw.c raycasting/vec_utils.c

SRC = main.c $(RAYCAST)

OBJ = $(SRC:.c=.o)

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(MLX42FLAGS_MAC) -o $@ $(LIBFT)

$(LIBFT): $(LIBFT_SRC)
	make -C libft all
	mv libft/libft.a .

%.o: %.c include/cub3D.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
