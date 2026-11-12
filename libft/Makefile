# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jde-sain <jde-sain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/18 18:10:37 by jde-sain          #+#    #+#              #
#    Updated: 2025/09/19 18:48:16 by jde-sain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_addstr_to_tab.c		\
		ft_removestr_tab.c		\
		ft_sort_strtab.c		\
		ft_char_kill.c			\
		ft_print_tab.c			\
		ft_free_tab.c			\
		ft_found_char.c			\
		ft_atoll.c				\
		ft_str_isdigit.c		\
		ft_swap_char.c			\
		ft_swap_str.c			\
		sprint.c				\
		iprint.c				\
								\
		ft_atoi.c				\
		ft_bzero.c				\
		ft_calloc.c				\
		ft_isalnum.c			\
		ft_isalpha.c			\
		ft_isascii.c			\
		ft_isdigit.c			\
		ft_isprint.c			\
		ft_itoa.c				\
		ft_memchr.c				\
		ft_memcmp.c				\
		ft_memcpy.c				\
		ft_memmove.c			\
		ft_memset.c				\
		ft_printf.c				\
		ft_printf_utils.c		\
		ft_dprintf.c			\
		ft_putchar_fd.c			\
		ft_putendl_fd.c			\
		ft_putnbr_fd.c			\
		ft_putstr_fd.c			\
		ft_split.c				\
		ft_strchr.c				\
		ft_strdup.c				\
		ft_strndup.c			\
		ft_striteri.c			\
		ft_strjoin.c			\
		ft_strcat.c				\
		ft_strlcat.c			\
		ft_strcpy.c				\
		ft_strlcpy.c			\
		ft_strlen.c				\
		ft_strmapi.c			\
		ft_strcmp.c				\
		ft_strncmp.c			\
		ft_strnstr.c			\
		ft_strrchr.c			\
		ft_strtrim.c			\
		ft_substr.c				\
		ft_swap.c				\
		ft_tablen.c				\
		ft_tolower.c			\
		ft_toupper.c			\
		get_next_line.c			\
		get_next_line_utils.c	\

SRC_BONUS =

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Wall -Werror -Wextra -g3

all : $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) libft.h
	ar -rcs $(NAME) $(OBJ)

bonus: $(OBJ_BONUS) $(OBJ)
	ar -rcs $(NAME) $(OBJ_BONUS) $(OBJ)

clean:
	rm -rf $(OBJ) $(OBJ_BONUS) ./a.out

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
