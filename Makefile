# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/16 19:30:49 by jtaylor           #+#    #+#              #
#    Updated: 2019/07/09 13:21:04 by jtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror -I ./libft/includes

DEBUG_FLAG = -g

SRC = ft_ls_list_handle.c ft_ls_main.c ft_ls_misc.c ft_ls_printing.c\
		ft_ls_read_info.c ft_ls_recursion.c ft_ls_sorting.c ft_sl_get_mode.c

.PHONY = all clean fclean re

all : $(NAME)

$(NAME) :
	@make -C ./libft
	@echo "\tBuilding ft_ls executable\n"
	@gcc $(FLAGS) $(SRC) -I ./includes ./libft/libft.a ./libft/ft_printf/libftprintf.a -o ft_ls
	@chmod 755 ./ft_ls

debug :
	@make -C ./libft
	@echo "\tBuilding ft_ls debug executable\n"
	@gcc $(FLAGS) $(SRC) $(DEBUG_FLAG) -I ./includes ./libft/libft.a ./libft/ft_printf/libftprintf.a -o ft_ls
	@chmod 755 ./ft_ls


clean :
	@echo "\tRemoving files\n"
	@make -C libft clean

fclean : clean
	@echo "\tRemoving Executable\n"
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@make -C libft fclean

re : fclean all
