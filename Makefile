CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -g

MLX42FLAGS_LINUX= libmlx42_linux.a -Iinclude -ldl -lglfw -pthread -lm
MLX42FLAGS_MAC= libmlx42_mac.a -Iinclude -lglfw

RAYCAST = raycasting/hooks.c raycasting/utils.c raycasting/init_actor_data.c
SOURCES = \
	main.c \
	parcing/validate_file/parsing.c parcing/validate_file/check_configure.c parcing/validate_file/configuration_tools.c parcing/validate_file/function_out.c \
	parcing/validate_file/ft_split.c parcing/validate_file/map.c parcing/validate_file/valide_map.c\

SRC = main.c $(RAYCAST) $(SOURCES)

OBJ = $(SRC:.c=.o)

NAME = cub3D
# Libraries
LIBFT_DIR = utils/libft
PRINTF_DIR = utils/ft_printf
GNL_DIR = utils/get_next_line

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/ft_printf.a
GNL = $(GNL_DIR)/get_next_line.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(GNL)
	$(CC) $(CFLAGS) $^ $(MLX42FLAGS_LINUX) $(LIBFT) $(PRINTF) $(GNL) -o $@

%.o: %.c include/cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

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
	@rm -f $(OBJECTS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean

re: all clean
