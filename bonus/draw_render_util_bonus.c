/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render_util_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:45:00 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:00:25 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	draw_sprite(t_var *var, t_sprite *sprite, int x)
{
	t_draw_sprite_var	tmp;

	tmp.sh = get_wall_height(sprite->sdist);
	tmp.y0 = (int)((SCREEN_HEIGHT - tmp.sh) / 2.0);
	tmp.y1 = tmp.y0 + tmp.sh - 1;
	tmp.lum = get_luminosity(var, sprite->sdist);
	tmp.ystart = max(0, tmp.y0);
	tmp.yend = min(SCREEN_HEIGHT - 1, tmp.y1);
	tmp.y = tmp.ystart;
	while (tmp.y <= tmp.yend)
	{
		tmp.ty = (int)((double)((tmp.y - tmp.y0) * 64) / tmp.sh);
		tmp.color = var->texture[var->rand]
			.texture_image[64 * tmp.ty + sprite->stx];
		tmp.color = fade_color(tmp.color, tmp.lum);
		var->image.addr[tmp.y * var->image.size_line / 4 + \
				(x + 10 + var->game.map_width * PIXEL_SIZE)] = tmp.color;
		tmp.y++;
	}
}

static void	draw_ceil_floor(t_var *var, int x, int y1)
{
	double	ec;
	int		y;
	double	h;
	double	d;
	double	lum_f;

	ec = get_fov_min_dist();
	y = y1 + 1;
	while (y < SCREEN_HEIGHT)
	{
		h = (double)(SCREEN_HEIGHT - 1 - y) / SCREEN_HEIGHT;
		d = ec / (1. - 2 * h);
		lum_f = get_luminosity(var, d) - 0.2;
		var->image.addr[y * var->image.size_line / 4
			+ (x + 10 + var->game.map_width * PIXEL_SIZE)]
			= fade_color(var->image.ceilling_color, lum_f);
		var->image.addr[(SCREEN_HEIGHT - 1 - y) * var->image.size_line / 4
			+ (x + 10 + var->game.map_width * PIXEL_SIZE)]
			= fade_color(var->image.floor_color, lum_f);
		y++;
	}
}

void	draw_wall(t_var *var, t_wall *wall, int x)
{
	t_draw_wall_var	tmp;

	tmp.wh = get_wall_height(wall->wdist);
	tmp.y0 = (int)((SCREEN_HEIGHT - tmp.wh) / 2.0);
	tmp.y1 = tmp.y0 + tmp.wh - 1;
	tmp.lum = get_luminosity(var, wall->wdist);
	tmp.y = max(0, tmp.y0);
	tmp.yend = min(SCREEN_HEIGHT - 1, tmp.y1);
	while (tmp.y <= tmp.yend)
	{
		tmp.ty = (int)((double)((tmp.y - tmp.y0) * 64) / tmp.wh);
		tmp.tex = wall->wdir;
		if (wall->door == CLOSE_DOOR)
			tmp.tex = DIR_DOOR;
		tmp.color = var->texture[tmp.tex]
			.texture_image[64 * tmp.ty + wall->wtx];
		tmp.color = fade_color(tmp.color, tmp.lum);
		var->image.addr[tmp.y * var->image.size_line / 4
			+ (x + 10 + var->game.map_width * PIXEL_SIZE)] = tmp.color;
		tmp.y++;
	}
	if (tmp.y1 < SCREEN_HEIGHT - 1)
		draw_ceil_floor(var, x, tmp.y1);
}
