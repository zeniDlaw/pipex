NAME = pipex

SRC = pipex.c process.c cmdnerr.c utils.c

OBJ = $(SRC:.c=.o)

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror

LIBFTPRINTF = ./ft_printf/libftprintf.a
LIBFTPRINTF_DIR = ./ft_printf

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) $(LIBFTPRINTF) $(LIBFT) -o $(NAME) $(CFLAGS)

%.o: %.c $(LIBFTPRINTF) $(LIBFT) 
		$(CC) $(CFLAGS) -I$(LIBFTPRINTF_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFTPRINTF):
	make -C $(LIBFTPRINTF_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFTPRINTF_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTPRINTF_DIR) fclean
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
