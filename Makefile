# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:34:28 by aalhalab          #+#    #+#              #
#    Updated: 2024/03/24 23:34:21 by aalhalab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_C = client
NAME_S = server
NAME_C_BONUS = client_bonus
NAME_S_BONUS = server_bonus
CFLAGS = -Wall -Wextra -Werror
CC = cc

SRC_C = client.c
OBJ_C = $(SRC_C:.c=.o)
SRC_S = server.c
OBJ_S = $(SRC_S:.c=.o)

SRC_C_BONUS = client_bonus.c
OBJ_C_BONUS = $(SRC_C_BONUS:.c=.o)
SRC_S_BONUS = server_bonus.c
OBJ_S_BONUS = $(SRC_S_BONUS:.c=.o)

LIBFT = ft_printf/libftprintf.a
LIBFT_DIR = ft_printf/

all : $(NAME_C) $(NAME_S)

$(NAME_C): $(OBJ_C) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_S): $(OBJ_S) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

bonus : $(NAME_C_BONUS) $(NAME_S_BONUS)

$(NAME_C_BONUS): $(OBJ_C_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_S_BONUS): $(OBJ_S_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME_C) $(NAME_S) $(NAME_C_BONUS) $(NAME_S_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus