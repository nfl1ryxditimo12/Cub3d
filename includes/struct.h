/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:52:34 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/01 17:47:41 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_image			t_image;
typedef struct s_game			t_game;
typedef struct s_var			t_var;
typedef struct s_texture		t_texture;

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
	t_map		**map;	// N x M 만큼의 동적할당
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
	void		*mlx;
	void		*win;
	t_game		game;
	t_image		image;
	t_texture	*texture; // N개의 텍스쳐 만큼 동적할당
};

#endif