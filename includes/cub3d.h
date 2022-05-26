/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:55:25 by seunpark          #+#    #+#             */
/*   Updated: 2022/05/24 21:57:16 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"

# define ESSENTIAL_ELEMENTS 7		// Except map content, N,S,E and W file path & floor, ceilling color
# define MAP_FILE_EXTENSION ".cub"

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

struct	s_texture_data
{
	char	*file_path;
	int		width;
	int		height;
};

struct	s_image
{
	void	*img;
	void	*addr;
	int		bit_per_pixel;
	int		size_line;
	int		endian;
};

struct	s_game
{
	enum e_map	**map;
	int			width;
	int			height;
};

struct	s_var
{
	t_mlx		mlx;
	t_texture	*image;
};

#endif
