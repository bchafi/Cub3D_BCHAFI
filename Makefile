CC = cc

# Libraries
LIBFT_DIR = utils/libft
PRINTF_DIR = utils/ft_printf
GNL_DIR = utils/get_next_line

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/ft_printf.a
GNL = $(GNL_DIR)/get_next_line.a

CFLAGS = -Wall -Werror -Wextra -g

MLX42FLAGS_LINUX= libmlx42_linux.a -Iinclude -ldl -lglfw -pthread -lm
MLX42FLAGS_MAC= libmlx42_mac.a -Iinclude -lglfw

SOURCES = main.c parcing/first_march.c parcing/parsing.c parcing/check_configure.c \
		parcing/configuration_tools.c parcing/function_out.c \
		parcing/ft_split.c parcing/map.c parcing/valide_map.c\

SRC = main.c $(SOURCES)

OBJ = $(SRC:.c=.o)

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(GNL)
	$(CC) $(CFLAGS) $^  $(LIBFT) $(PRINTF) $(GNL) -o $@ $(MLX42FLAGS_LINUX)

%.o: %.c include/cub3D.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "DONE Compiler LIBFT!!"

$(PRINTF):
	@$(MAKE) -C $(PRINTF_DIR)
	@echo "DONE Compiler PRINTF!!"

$(GNL):
	@$(MAKE) -C $(GNL_DIR)
	@echo "DONE Compiler GNL!!"

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean

run: clean all
	@./cub3D ./map/map1.cub

re: fclean all
