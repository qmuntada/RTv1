# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/07 16:04:22 by qmuntada          #+#    #+#              #
#    Updated: 2015/01/17 17:06:00 by qmuntada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CFLAGS = -Wall -Werror -Wextra
SRC = display.c env.c event.c get.c get2.c inter.c light.c light2.c main.c \
		obj.c parser.c pixel.c reader.c shadows.c
OBJ = $(SRC:.c=.o)
LIBX = -lm -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lmlx -L libft/ -lft
LIBXL = -L libft/ -lft -L/usr/lib/X11 -lmlx -lXext -lX11 -lm

all : $(NAME)

.PHONY : libft linux clean fclean re norme

$(NAME) : libft
	@echo "Creating MAC executable $@ ..."
	@gcc $(CFLAGS) -c $(SRC) $(LIBX)
	@gcc -o $(NAME) $(OBJ) $(LIBX)

linux : libft
	@echo "Creating LINUX executable $@ ..."
	@gcc $(CFLAGS) -c $(SRC) $(LIBXL)
	@gcc -o $(NAME) $(OBJ) $(LIBXL)

libft:
	@make -C libft fclean
	@make -C libft

clean :
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re : fclean all
