NAME = libgnl.a
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror

SOURCES = \
	get_next_line.c \
	get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

%.o: %.c get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(AR) -rc $(NAME) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)
	@echo "Clean GNL!!"

fclean: clean
	@rm -f $(NAME)
	@echo "Fclean GNL!!"

re: fclean all
