#ifndef INIT_H
# define INIT_H

# include "mlx.h"

# define ESSENTIAL_ELEMENTS 7		// Except map content, N,S,E and W file path & floor, ceilling color
# define MAP_FILE_EXTENSION ".cub"

enum Elements
{
	SPACE,
	WALL,
	DOOR,
	SPRITE,
	SOUTH,
	NORTH,
	WEST,
	EAST,
	EMPTY_SPACE
};

typedef struct	s_mlx
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct s_image
{
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	void	*floor;
	void	*ceilling;
}				t_image;

typedef struct s_game
{
	enum Elements	**map;
	int				width;
	int				height;
}				t_game;

typedef struct	s_var
{
	t_mlx	mlx;
	t_image	*image;
}				t_var;

#endif