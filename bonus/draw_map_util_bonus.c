/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_util_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:43:46 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:00:50 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_line(t_image *image, t_offset p1, t_offset p2, int color)
{
	double	delta_x;
	double	delta_y;
	double	step;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	if (fabs(delta_x) > fabs(delta_y))
		step = fabs(delta_x);
	else
		step = fabs(delta_y);
	delta_x /= step;
	delta_y /= step;
	while (fabs(p2.x - p1.x) > 1 || fabs(p2.y - p1.y) > 1)
	{
		image->addr[(int)round(p1.y) * image->size_line / \
					4 + (int)round(p1.x)] = color;
		p1.x += delta_x;
		p1.y += delta_y;
	}
}

// draw in minimap
void	draw_rectangle(t_var *var, int x, int y, int color)
{
	int	i;
	int	j;

	x *= PIXEL_SIZE;
	y *= PIXEL_SIZE;
	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
			var->image.addr[(y + i) * var->image.size_line / 4 + x + j] = color;
	}
}

void	draw_rectangles(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	while (++i < var->game.map_height)
	{
		j = -1;
		while (++j < var->game.map_width)
		{
			if (var->game.map[i][j] == WALL)
				draw_rectangle(var, j, i, WALL_COLOR);
			else if (var->game.map[i][j] == FLOOR)
				draw_rectangle(var, j, i, FLOOR_COLOR);
		}
	}
}
