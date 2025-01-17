# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akorol <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/03 13:23:40 by akorol            #+#    #+#              #
#    Updated: 2019/06/03 13:23:41 by akorol           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC =   main.c	\
		file.c	\
		file1.c \
		file2.c \
		file3.c \
		file5.c \
		array_manipulation.c \
		deleting_links.c \
		data_tunage.c \
		queue_action.c \
		delete_out_forks.c \
		lems.c \
		file10.c \
		save_links.c \
		support.c

CFLAGS = -Wextra -Wall -Werror

LIB = libft/libft.a

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):$(LIB) $(OBJ)
	gcc -g -o $@ $(OBJ) $(LIB)

$(OBJ):%.o:%.c
	gcc $(CFLAGS) -c $< -o $@

$(LIB):
	make -C libft/

clean:
	make clean -C libft
	rm -f *.o

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all