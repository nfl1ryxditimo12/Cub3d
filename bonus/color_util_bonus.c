/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:40:39 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:01:21 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// aka. blur
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

void	decode_color(int color, int *r, int *g, int *b)
{
	*r = color & 0x00ff0000;
	*r = *r >> 16;
	*g = color & 0x0000ff00;
	*g = *g >> 8;
	*b = color & 0x000000ff;
}

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
