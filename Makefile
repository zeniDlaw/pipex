# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichettri <ichettri@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 12:39:32 by ichettri          #+#    #+#              #
#    Updated: 2024/07/02 15:07:27 by ichettri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

SRC = src_man/pipex.c src_man/process.c src_man/cmdnerr.c src_man/man_utils.c
OBJ = $(SRC:.c=.o)

BONUS = src_bon/pipex_bonus.c src_bon/utils_bonus.c src_bon/utils_bonus2.c
BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

LIBFTPRINTF = ./ft_printf/libftprintf.a
LIBFTPRINTF_DIR = ./ft_printf

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFTPRINTF) $(LIBFT)
	$(CC) $(OBJ) $(LIBFTPRINTF) $(LIBFT) -o $(NAME) $(CFLAGS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFTPRINTF) $(LIBFT)
	$(CC) $(BONUS_OBJS) $(LIBFTPRINTF) $(LIBFT) -o $(BONUS_NAME) $(CFLAGS)

%.o: %.c $(LIBFTPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) -I$(LIBFTPRINTF_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFTPRINTF):
	make -C $(LIBFTPRINTF_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ) $(BONUS_OBJS)
	make -C $(LIBFTPRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIBFTPRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
