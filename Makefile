# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 18:28:19 by vpozniak          #+#    #+#              #
#    Updated: 2025/03/24 18:30:58 by vpozniak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm
MLX_PATH= mlx
MLX_LIB = $(MLX_PATH)/libmlx_Linux.a


SRCS = test.c
OBJS = $(SRCS:.c=.o)

all: sublib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS)  $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

sublib:
	@make -C $(MLX_PATH) all

clean:
	rm -f $(OBJS)
	@make -C $(MLX_PATH) clean_obj

 fclean: clean
	make -C $(MLX_PATH) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re sublib
