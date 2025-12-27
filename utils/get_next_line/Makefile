NAME = get_next_line.a
CC = cc
AR = ar -rc

CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

SOURCES = \
	get_next_line.c \
	get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(AR) $@ $^


%.o : %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all
