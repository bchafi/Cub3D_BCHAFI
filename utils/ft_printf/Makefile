# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 02:34:22 by bchafi            #+#    #+#              #
#    Updated: 2024/12/08 02:34:24 by bchafi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a
HEADER = ft_printf.h
CC = cc
AR = ar -rc
CFLAGS = -Wall -Wextra -Werror

SOURCES = \
	ft_printf.c \
	ft_printf_utils.c
	
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
