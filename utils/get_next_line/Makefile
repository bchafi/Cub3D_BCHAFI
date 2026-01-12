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
	@echo "get_next_line library compiled successfully!"

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
