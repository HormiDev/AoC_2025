# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 17:09:57 by ide-dieg          #+#    #+#              #
#    Updated: 2025/12/02 15:12:22 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC_PARTE1 = parte1.c
SRC_PARTE2 = parte2.c
LIB = ../42_Libft/libft.a
NAME = $(notdir $(CURDIR))

all:
	@git submodule update --init --recursive > /dev/null 2>&1
	make all -C ../42_Libft > /dev/null 2>&1; \
	$(CC) $(CFLAGS) $(SRC_PARTE1) $(LIB) -o $(NAME)_parte1.out
	$(CC) $(CFLAGS) $(SRC_PARTE2) $(LIB) -o $(NAME)_parte2.out

clean:
	@make fclean -C ../42_Libft > /dev/null 2>&1
	rm -f $(NAME)_parte1.out $(NAME)_parte2.out