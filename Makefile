# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 15:38:31 by sgalasso          #+#    #+#              #
#    Updated: 2018/11/17 14:12:36 by sgalasso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = srcs/main.c \
	  srcs/ft_utils.c \
	  srcs/ft_init_lst.c \
	  srcs/ft_init_data.c \
	  srcs/ft_builtins.c \
	  srcs/ft_change_dir.c \
	  srcs/ft_find_binary.c \
	  srcs/ft_parse_command.c \
	  srcs/ft_replace_alias.c \
	  srcs/ft_free_and_exit.c \
	  srcs/ft_errors.c \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/

all:	lib $(NAME)

$(NAME):	$(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) libft/libft.a $(OBJ) -I $(INCLUDES)

lib:
	make -C libft/

%.o: %.c $(INCLUDES)minishell.h Makefile
	gcc -Wall -Wextra -Werror -o $@ -c $< -I $(INCLUDES)

clean:
	rm -f $(OBJ) && make -C libft/ clean

fclean:		clean
	rm -f $(NAME) && make -C libft/ fclean

re:			fclean all

.PHONY : all clean fclean re
