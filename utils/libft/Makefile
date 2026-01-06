NAME = libft.a
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror
SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_strlen.c \
	ft_strlcpy.c ft_strchr.c ft_bzero.c \
	ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_strlcat.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_memset.c ft_strtrim.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_strcmp.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

%.o : %.c libft.h
	@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@$(AR) -rc $@ $^

clean:
	@rm -f $(OBJECTS) $(OBJECTSB)
	@echo "Clean LIBFT!!"

fclean: clean
	@rm -f $(NAME)
	@echo "Fclean LIBFT!!"

re: fclean all
