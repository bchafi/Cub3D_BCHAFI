# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror# -g3 -fsanitize=address

# Executable name
NAME = cub3D

# Libraries
LIBFT_DIR = utils/libft
PRINTF_DIR = utils/ft_printf
GNL_DIR = utils/get_next_line

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/ft_printf.a
GNL = $(GNL_DIR)/get_next_line.a

# Sources of your project (only your own .c files)
SOURCES = \
	main.c \
	validate_file/parsing.c validate_file/check_configure.c validate_file/configuration_tools.c validate_file/function_out.c \
	validate_file/ft_split.c validate_file/map.c validate_file/valide_map.c\

OBJECTS = $(SOURCES:.c=.o)

# ===================== RULES =====================

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(PRINTF) $(GNL)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME)
	@echo "DONE Compiler Cub3D!!"

%.o: %.c cub3D.h
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
