/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:43:46 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:46:35 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// x1 부터 x2, y1 부터 y2 까지 선 그리는 함수
void	draw_line(t_image *image, double x1, double y1, double x2, double y2, int color)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 1 || fabs(y2 - y1) > 1)
	{
		image->addr[(int)round(y1) * image->size_line / 4 + (int)round(x1)] = color;
		x1 += deltaX;
		y1 += deltaY;
	}
}

// 미니맵 한칸 그려주는 함수
void	draw_rectangle(t_var *var, int x, int y, int color)
{
	int i;
	int j;

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

// 미니맵 그리는 함수
void	draw_rectangles(t_var *var)
{
	int i;
	int j;

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