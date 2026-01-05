CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

NAME = cub3D

LIBFT_DIR = utils/libft
GNL_DIR = utils/get_next_line

LIBFT = $(LIBFT_DIR)/libft.a
GNL = $(GNL_DIR)/libgnl.a

SOURCES = main.c \
		  parcing/parsing.c \
		  parcing/check_configure.c \
		  parcing/configuration_tools.c \
		  parcing/function_out.c \
		  parcing/ft_split.c \
		  parcing/map.c \
		  parcing/valide_map.c \

OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) -o $@

%.o: %.c include/parcing.h
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

re: fclean all

run: all
	./cub3D map/map1.cub

