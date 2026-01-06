CC = cc

LIBFT_DIR = ./utils/libft
GNL_DIR = ./utils/get_next_line

GNL = $(GNL_DIR)/libgnl.a
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC = ./Helpers/keys_events.c \
      ./Helpers/Pixel_Draw.c \
      ./Helpers/Math.c \
      ./GC/Garbage_Collector.c \
		./Helpers/Draw.c \
		./Helpers/Ray_casting_H.c \
		./Helpers/Ray_Casting.c \
		./Helpers/functions.c \
		./Helpers/Functions.c \
      	Core.c \
		main.c bonus.c \
		  parcing/parsing.c \
		  parcing/check_configure.c \
		  parcing/configuration_tools.c \
		  parcing/function_out.c \
		  parcing/ft_split.c \
		  parcing/map.c \
		  parcing/valide_map.c \


OBJ = $(SRC:.c=.o)

MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

NAME = cub3d

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) $(MLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean

run :
	make re && make clean && ./cub3d ./map/map1.cub

re: fclean all

push : 
	git add . && git commit -m "update" &&  git push