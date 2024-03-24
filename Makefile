# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 12:34:28 by aalhalab          #+#    #+#              #
#    Updated: 2024/03/24 22:44:13 by aalhalab         ###   ########.fr        #
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

all : $(NAME_C) $(NAME_S)
$(NAME_C): $(OBJ_C) $(OBJ_L)
    $(CC) $(CFLAGS) $^ -o $@
$(NAME_S): $(OBJ_S) $(OBJ_L)
    $(CC) $(CFLAGS) $^ -o $@

bonus : $(NAME_C_BONUS) $(NAME_S_BONUS)
$(NAME_C_BONUS): $(OBJ_C_BONUS) $(OBJ_L)
    $(CC) $(CFLAGS) $^ -o $@
$(NAME_S_BONUS): $(OBJ_S_BONUS) $(OBJ_L)
    $(CC) $(CFLAGS) $^ -o $@
	
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@
clean:
    rm -rf *.o ft_printf/*.o
fclean: clean
    rm -rf $(NAME_C) $(NAME_S) $(NAME_C_BONUS) $(NAME_S_BONUS)
re: fclean all
