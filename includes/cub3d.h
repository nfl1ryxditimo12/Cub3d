/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:55:25 by seunpark          #+#    #+#             */
/*   Updated: 2022/05/26 21:12:54 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define ESSENTIAL_ELEMENTS 6		// Except map content, N,S,E and W file path & floor, ceilling color
# define MAP_FILE_EXTENSION ".cub"

#define WIDTH		1600
#define HEIGHT		1000
#define MAP_COL		15
#define MAP_ROW		11
#define PIXEL_SIZE	32
#define WALL_DEFAULT_HEIGHT	1000

# define PLAYER_COLOR	0xFF0000
# define WALL_COLOR		0x333333
# define SPACE_COLOR	0x999999
# define GRID_COLOR		0xb3b3b3
# define DIR_COLOR		0xFFFF66

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code

#define KEY_ESC			53
#define KEY_W			13
#define KEY_S			1
#define KEY_A			0
#define KEY_D			2
#define KEY_LEFT		123
#define KEY_RIGHT		124

typedef struct s_mlx			t_mlx;
typedef struct s_image			t_image;
typedef struct s_game			t_game;
typedef struct s_var			t_var;
typedef struct s_texture		t_texture;
typedef struct s_texture_data	t_texture_data;


enum e_map
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

struct	s_mlx
{
	int		window_width;
	int		window_height;
	void	*mlx;
	void	*win;
};
struct	s_texture_data
{
	char	*file_path;
	int		width;
	int		height;
};

struct	s_texture
{
	t_texture_data	north;
	t_texture_data	south;
	t_texture_data	west;
	t_texture_data	east;
	t_texture_data	floor;
	t_texture_data	ceilling;
	t_texture_data	door;
	t_texture_data	sprite;
};

struct	s_image
{
	void	*image;
	int		*addr;
	int		bit_per_pixel;
	int		size_line;
	int		endian;
};

struct	s_game
{
	enum e_map	**map;
	int			width;
	int			height;
	double		player_pos_x;
	double		player_pos_y;
};

struct	s_var
{
	t_game		game;
	t_mlx		mlx;
	t_image		map;
	t_image		division;
	t_image		render;
	t_texture	textures;
	double		angle;
};

/* utils.c */
int	ft_strlen(char *str);

void	draw_mini_map(t_var *var);

void	draw_rays(t_var *var);
void	draw_line(t_image *image, double x1, double y1, double x2, double y2, int color);
int		deal_key(int key_code, t_var *var);
int 	close(t_var *var);

#endif