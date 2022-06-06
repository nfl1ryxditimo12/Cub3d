/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:45:00 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 21:16:04 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// sprite 그려줌
void	draw_sprite(t_var *var, t_sprite *sprite, int x)
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

	sh = get_wall_height(sprite->sdist);
	y0 = (int)((SCREEN_HEIGHT - sh) / 2.0);
	y1 = y0 + sh - 1;
	lum = get_luminosity(var, sprite->sdist);
	ystart = max(0, y0);
	yend = min(SCREEN_HEIGHT - 1, y1);
	y = ystart;
	while (y <= yend)
	{
		ty = (int)((double)((y - y0) * 64) / sh);
		color = var->texture[var->rand].texture_image[64 * ty + sprite->stx];
		color = fade_color(color, lum);
		var->image.addr[y * var->image.size_line / 4 + \
				(x + 10 + var->game.map_width * PIXEL_SIZE)] = color;
		y++;
	}
}

// 벽그려주는 함수
void	draw_wall(t_var *var, t_wall *wall, int x)
{
    int wh = get_wall_height(wall->wdist);
    int y0 = (int)((SCREEN_HEIGHT - wh)/2.0);
    int y1 = y0 + wh - 1;
	double lum = get_luminosity(var, wall->wdist);
    int ystart = max(0, y0);
    int yend = min(SCREEN_HEIGHT-1, y1);

	for (int y = ystart; y <= yend; y++) {
		int ty = (int)((double)(y - y0) * 64 / wh);
		int tex = wall->door == CLOSE_DOOR ? DIR_DOOR : wall->wdir;
		int color = var->texture[tex].texture_image[64 * ty + wall->wtx];
		color = fade_color(color, lum);
		var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = color;
	}

	// 천장과 바닥 그려주는 부분
	if (y1 < SCREEN_HEIGHT - 1)
	{
		double ec = get_fov_min_dist();

		for (int y = y1 + 1; y < SCREEN_HEIGHT; y++)
		{
			double h = (double)(SCREEN_HEIGHT - 1 - y) / SCREEN_HEIGHT;
            double D = ec / (1. - 2 * h);
            double lum_f = get_luminosity(var, D) - 0.2;

			var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = fade_color(var->image.ceilling_color, lum_f);
			var->image.addr[(SCREEN_HEIGHT - 1 -y) * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = fade_color(var->image.floor_color, lum_f);
		}
	}
}