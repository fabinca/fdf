# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 14:57:03 by cfabian           #+#    #+#              #
#    Updated: 2022/02/16 18:46:40 by cfabian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
SRC	= 	$(SRC_DIR)/draw_map.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/key_press.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/parse_map.c\
		$(SRC_DIR)/render_window.c 
		
OBJ_DIR = obj
OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
CFLAGS	= -Wall -Werror -Wextra
CC = gcc
MLX = libmlx.a
NAME = fdf
LIB = libft.a

all	: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIB):
	@make -C ./libft/
	mv -u ./libft/$(LIB) ./$(LIB)
	cp -u ./libft/libft.h ./libft.h
	
$(MLX) :
	cd ./mlx_lx && ./configure
	cd ..
	mv -u ./mlx_lx/$(MLX) ./$(MLX)
	cp -u ./mlx_lx/mlx.h ./mlx.h

$(NAME)	: $(OBJ) $(MLX) $(LIB)
#	@$(CC) -g -o $(NAME) $(OBJ) $(MLX) $(LIB) -lXext -lX11
	$(CC) $(OBJ) $(LIB) $(MLX) -Lmlx_linux -L/usr/lib -lXext -lX11 -lm -lz -g -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(MLX) $(LIB)
	make -C mlx_lx clean
	make -C libft fclean


re: fclean all

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf not_a_map
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fdf test_maps/10-2.fdf

norm:
	norminette $(SRC) $(INCL)
	make -C libft norm


.PHONY: all memcheck test bonus clean fclean re norm
