# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 21:04:46 by seunpark          #+#    #+#              #
#    Updated: 2022/05/24 21:08:16 by seunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
CDEBUGFLAGS		=	-fsanitize=address

INC_DIR			=	includes/
# CONTAINER_INC	=	$(INC_DIR)/
# ITERATOR_INC	=	$(INC_DIR)/iterators/
# UTIL_INC		=	$(INC_DIR)/utils/
MLX_DIR			=	minilibx_mms_20210621/
OBJ_DIR			=	objects/
SRC_DIR			=	sources/

SOURCES			=	main.c\

MLX_DYLIB		=	libmlx.dylib

OBJ_FILES		=	$(SOURCES:.c=.o)
OBJECTS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

MKDIR			=	$(shell mkdir $(OBJ_DIR) 2> /dev/null)

all		:	$(MKDIR) $(NAME)

debug	:	CFLAGS += $(CXXDEBUGFLAGS)
debug	:	re

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME)	:	$(OBJECTS)
	make --directory=$(MLX_DIR)
	cp ./$(MLX_DIR)$(MLX_DYLIB) ./
	$(CC) $(CFLAGS) -L./ -lmlx $(OBJECTS) -o $(NAME)

clean	:
	rm -rf $(OBJ_DIR)
	rm -rf .vscode

fclean	:	clean
	rm -rf $(NAME)

re		:
	make fclean
	make all

.PHONY: all clean fclean re debug
