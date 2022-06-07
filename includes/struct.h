/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:52:34 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 19:22:22 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_image				t_image;
typedef struct s_game				t_game;
typedef struct s_var				t_var;
typedef struct s_texture			t_texture;
typedef struct s_wall				t_wall;
typedef struct s_sprite				t_sprite;
typedef struct s_draw_wall_var		t_draw_wall_var;
typedef struct s_draw_sprite_var	t_draw_sprite_var;
typedef struct s_offset				t_offset;
typedef struct s_intersection	t_intersection;

struct	s_offset
{
	double	x;
	double	y;
};

struct	s_draw_wall_var
{
	int		wh;
	int		y0;
	int		y1;
	double	lum;
	int		yend;
	int		y;
	int		ty;
	int		tex;
	int		color;
};

struct	s_draw_sprite_var
{
	double	lum;
	int		sh;
	int		y0;
	int		y1;
	int		ystart;
	int		yend;
	int		y;
	int		ty;
	int		color;
};

struct	s_texture
{
	int		*texture_image;
	int		texture_width;
	int		texture_height;
};

struct	s_image
{
	void	*image;
	int		*addr;
	int		bit_per_pixel;
	int		size_line;
	int		endian;
	int		image_width;
	int		image_height;
	int		floor_color;
	int		ceilling_color;
};

struct	s_game
{
	t_map		**map;
	int			map_width;
	int			map_height;
	double		px;
	double		py;
	double		m_px;
	double		m_py;
	double		angle;
};

struct	s_var
{
	int			rand;
	int			open;
	void		*mlx;
	void		*win;
	t_game		game;
	t_image		image;
	t_texture	*texture;
};

struct	s_wall
{
	t_dir	wdir;
	t_map	door;
	int		wtx;
	int		dmapx;
	int		dmapy;
	double	wx;
	double	wy;
	double	dx;
	double	dy;
	double	wdist;
	double	ddist;
};

struct	s_sprite
{
	t_dir	sdir;
	int		stx;
	double	sx;
	double	sy;
	double	sdist;
};

struct	s_intersection
{
	int		cell;
	int		mapx;
	int		mapy;
	int		xstep;
	int		ystep;
	int		hit;
	int		hit_side;
	double	px;
	double	py;
	double	nx;
	double	ny;
	double	xslope;
	double	yslope;
	double	func;
	double	gunc;
	double	dist_v;
	double	dist_h;
};

#endif
