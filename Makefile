#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjamin	  <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 14:57:05 by bjamin            #+#    #+#              #
#    Updated: 2016/01/06 13:31:31 by bjamin           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#Define the program
NAME			= ft_ls
LIB				=	./libft/libft.a
_SRC			= 	ft_ls.c ft_ls_debug.c ft_ls_options.c  ft_ls_errors.c \
					ft_ls_read.c ft_ls_sort.c ft_ls_show.c ft_ls_sizes.c ft_ls_getters.c
INCLUDES		= -I./libft/includes/ -I./includes/
SRC				= $(addprefix srcs/,$(_SRC))
OBJ				= $(SRC:.c=.o)
CFLAGS			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft/
	@gcc $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES) -o $(NAME)
	@echo $(NAME)" compiled"


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "Clean all .o files"

fclean:	clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME)
	@echo "Clean all .o and .a"

re: fclean all
