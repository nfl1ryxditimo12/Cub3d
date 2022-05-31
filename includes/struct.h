/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:52:34 by seonkim           #+#    #+#             */
/*   Updated: 2022/05/31 18:05:49 by seonkim          ###   ########.fr       */
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
};

struct	s_game
{
	t_map		**map;
	int			width;
	int			height;
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
	t_texture	*texture;
};

#endif