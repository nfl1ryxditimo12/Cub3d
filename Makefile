# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 21:04:46 by seunpark          #+#    #+#              #
#    Updated: 2022/06/06 19:53:12 by seonkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g
CDEBUGFLAGS		=	-fsanitize=address
MLXFLAG			=	-lmlx -framework OpenGL -framework AppKit

ROOT_DIR		=	$(shell pwd)
INC_DIR			=	includes/
MLX_DIR			=	$(addprefix $(ROOT_DIR), /minilibx_mms_20210621/)
OBJ_DIR			=	objects/
SRC_DIR			=	sources/

SOURCES			=	main.c\
					finish.c\
					check_element_util.c\
					check_resize_util.c\
					check_wall_util.c\
					check.c\
					color_util.c\
					draw_map_util.c\
					draw_render_util.c\
					draw.c\
					init.c\
					key.c\
					libft_util.c\
					memory_util.c\
					parse_element_util.c\
					parse_file_util.c\
					parse_map_util.c\
					parse_util.c\
					parse.c\
					ray_casting_math_util.c\
					ray_casting.c

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
