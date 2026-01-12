CC = cc

LIBFT_DIR = ./utils/libft
GNL_DIR = ./utils/get_next_line

GNL = $(GNL_DIR)/libgnl.a
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC = ./helpers/keys_events.c \
      ./helpers/pixel_draw.c \
      ./helpers/math.c \
      ./helpers/garbage_collector.c \
	  ./helpers/draw.c \
	  ./helpers/ray_casting_h.c \
	  ./helpers/ray_casting.c \
	  ./helpers/functions.c \
	  ./helpers/func_help.c \
	  ./helpers/helper_function.c \
	  ./Core.c \
	  ./main.c \
	  parcing/parsing.c \
	  parcing/check_configure.c \
	  parcing/configuration_tools.c \
	  parcing/function_out.c \
	  parcing/ft_split.c \
	  parcing/map.c \
	  parcing/valide_map.c \
	  ./helpers/key_event2.c \

OBJ = $(SRC:.c=.o)

MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

NAME = cub3d

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(GNL)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) $(MLX) -o $(NAME)
	@echo "Cub3D compiled successfully!"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	@$(MAKE) -C $(GNL_DIR)
clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@echo "Cub3D object files cleaned successfully!"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@echo "Cub3D cleaned successfully!"

run :
	make re && make clean && ./cub3d ./map/map2.cub

re: fclean all

push : 
	git add . && git commit -m "update" &&  git push