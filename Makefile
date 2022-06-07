# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 21:04:46 by seunpark          #+#    #+#              #
#    Updated: 2022/06/07 21:45:10 by seunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g
CDEBUGFLAGS		=	-fsanitize=address
MLXFLAG			=	-lmlx

ROOT_DIR		=	$(shell pwd)
INC_BONUS_DIR	=	includes_bonus/
MLX_DIR			=	$(addprefix $(ROOT_DIR), /minilibx_mms_20210621/)

BONUS_DIR		=	bonus/
BONUS_SRC		=	main_bonus.c \
					finish_bonus.c \
					check_element_util_bonus.c \
					check_resize_util_bonus.c \
					check_wall_util_bonus.c \
					check_bonus.c \
					color_util_bonus.c \
					draw_map_util_bonus.c \
					draw_render_util_bonus.c \
					draw_bonus.c \
					init_bonus.c \
					key_bonus.c \
					libft_util_bonus.c \
					memory_util_bonus.c \
					parse_element_util_bonus.c \
					parse_file_util_bonus.c \
					parse_map_util_bonus.c \
					parse_util_bonus.c \
					parse_bonus.c \
					ray_casting_init_bonus.c \
					ray_casting_intersection_util_bonus.c \
					ray_casting_math_util_bonus.c \
					ray_casting_render_util_bonus.c \
					ray_casting_view_util_bonus.c \
					ray_casting_bonus.c

MLX_DYLIB		=	$(addprefix $(MLX_DIR), libmlx.dylib)

OBJ_DIR			=	objects/
OBJ_FILES		=	$(SOURCES:.c=.o)
OBJECTS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_BONUS_FILES	=	$(BONUS_SRC:.c=.o)
OBJECTS_BONUS	=	$(addprefix $(OBJ_DIR), $(OBJ_BONUS_FILES))

MKDIR			=	$(shell mkdir $(OBJ_DIR) 2> /dev/null)

all		:	$(MKDIR) $(NAME)

$(OBJ_DIR)%.o	:	$(BONUS_DIR)%.c
	$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(INC_BONUS_DIR) -c $< -o $@

$(NAME)	:	$(OBJECTS_BONUS)
	$(MAKE) -C $(MLX_DIR) all
	cp $(MLX_DYLIB) ./
	$(CC) $(CFLAGS) -L $(MLX_DIR) $(MLXFLAG) $(OBJECTS_BONUS) -o $(NAME)

bonus	: $(OBJECTS_BONUS)
	$(MAKE) -C $(MLX_DIR) all
	cp $(MLX_DYLIB) ./
	$(CC) $(CFLAGS) -L $(MLX_DIR) $(MLXFLAG) $(OBJECTS_BONUS) -o $(NAME)

clean	:
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf .vscode

fclean	:	clean
	rm -rf $(NAME)

re		:
	make fclean
	make all

.PHONY: all clean fclean re bonus
