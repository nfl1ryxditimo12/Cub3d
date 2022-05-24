NAME			=	cub3D
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
CDEBUGFLAGS		=	-fsanitize=address

INC_DIR			=	includes/
# CONTAINER_INC	=	$(INC_DIR)/
# ITERATOR_INC	=	$(INC_DIR)/iterators/
# UTIL_INC		=	$(INC_DIR)/utils/
MLX_DIR			=	mlx/
OBJ_DIR			=	objects/
SRC_DIR			=	sources/

SOURCES			=	main.c\

MLX_DYLIB		=	mlx/libmlx.dylib

OBJ_FILES		=	$(SOURCES:.c=.o)
OBJECTS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

MKDIR			=	$(shell mkdir $(OBJ_DIR) 2> /dev/null)

all		:	$(MKDIR) $(NAME)

debug	:	CFLAGS += $(CXXDEBUGFLAGS)
debug	:	re

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME)	:	$(OBJECTS)
	$(CC) $(CFLAGS) -I $(MLX_DIR) $(MLX_DYLIB) $(OBJECTS) -o $(NAME)

clean	:
	rm -rf $(OBJ_DIR)
	rm -rf .vscode

fclean	:	clean
	rm -rf $(NAME)

re		:
	make fclean
	make all

.PHONY: all clean fclean re debug