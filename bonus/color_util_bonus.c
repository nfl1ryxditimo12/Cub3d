/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:40:39 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 거리별 명암 조절해주는 함수
double	get_luminosity(t_var *var, double dist)
{
	double	lum;

	lum = -1;
	if (lum < 0)
		lum = (double)(var->game.map_width + var->game.map_height) / 2.0;
	if (dist > lum)
		return (0);
	return (1. - dist / lum);
}

// 200 200 200 int형으로 따로 있는 색을 합쳐주는 함수
int	encode_color(int r, int g, int b)
{
	int	color;

	color = r;
	color <<= 8;
	color += g;
	color <<= 8;
	color += b;
	return (color);
}

// 16진수 color code에서 r, g, b로 분리해주는 함수
void	decode_color(int color, int *r, int *g, int *b)
{
	*r = color & 0x00ff0000;
	*r = *r >> 16;
	*g = color & 0x0000ff00;
	*g = *g >> 8;
	*b = color & 0x000000ff;
}

// r, g, b 따로따로 거리를 따라 명암 조절해주는 함수
int	fade_color(int color, double lum)
{
	int	new_color;
	int	r;
	int	g;
	int	b;

	if (lum < 0)
		lum = 0;
	else if (lum > 1)
		lum = 1;
	decode_color(color, &r, &g, &b);
	new_color = encode_color((int)(r * lum), (int)(g * lum), (int)(b * lum));
	return (new_color);
}
