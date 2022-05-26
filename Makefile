# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 21:04:46 by seunpark          #+#    #+#              #
#    Updated: 2022/05/26 20:39:52 by seunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g -o3
CDEBUGFLAGS		=	-fsanitize=address
MLXFLAG			=	-lmlx -framework OpenGL -framework AppKit

ROOT_DIR		=	$(shell pwd)
INC_DIR			=	includes/
MLX_DIR			=	$(addprefix $(ROOT_DIR), /minilibx_mms_20210621/)
OBJ_DIR			=	objects/
SRC_DIR			=	sources/

SOURCES			=	main.c\

MLX_DYLIB		=	$(addprefix $(MLX_DIR), libmlx.dylib)

OBJ_FILES		=	$(SOURCES:.c=.o)
OBJECTS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

MKDIR			=	$(shell mkdir $(OBJ_DIR) 2> /dev/null)

all		:	$(MKDIR) $(NAME)

debug	:	CFLAGS += $(CXXDEBUGFLAGS)
debug	:	re

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(INC_DIR) -c $< -o $@

$(NAME)	:	$(OBJECTS)
	$(MAKE) -C $(MLX_DIR) all
	cp $(MLX_DYLIB) ./
	$(CC) $(CFLAGS) -L $(MLX_DIR) $(MLXFLAG) $(OBJECTS) -o $(NAME)

clean	:
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf .vscode

fclean	:	clean
	rm -rf $(NAME)

re		:
	make fclean
	make all

.PHONY: all clean fclean re debug
