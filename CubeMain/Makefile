CC = cc -g -fsanitize=address

LIBFT_DIR = utils/libft
GNL_DIR = utils/get_next_line

LIBFT = $(LIBFT_DIR)/libft.a
GNL = $(GNL_DIR)/libgnl.a

#CFLAGS =   -O3 -I/usr/include -Imlx_linux

SRC = ./Helpers/keys_events.c \
      ./Helpers/Pixel_Draw.c \
      ./Helpers/Math.c \
      ./GC/Garbage_Collector.c \
		./Helpers/Draw.c \
		./Helpers/Ray_casting_H.c \
		./Helpers/Ray_Casting.c \
      	Core.c main.c \
	parcing/parsing.c \
	parcing/check_configure.c \
	parcing/configuration_tools.c \
	parcing/function_out.c \
	parcing/ft_split.c \
	parcing/valide_map.c \
	parcing/map.c \


OBJ = $(SRC:.c=.o)

MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

NAME = cub3d

all: $(NAME)


$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(GNL) $(MLX) -o $(NAME)

%.o: %.c parcing.h
	$(CC) $(CFLAGS) -c $< -o $@

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
	make re && make clean
	./cub3d ./map/map1.cub

re: fclean all

push : 
	git add . && git commit -m "update" &&  git push