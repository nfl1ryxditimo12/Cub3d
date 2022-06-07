/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:38:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 19:07:17 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_element_coordinate(t_intersection *inter, t_wall *wall, \
											t_sprite *sprite)
{
	if (inter->cell == 1 || inter->cell == CLOSE_DOOR \
	|| inter->cell == OPEN_DOOR || (inter->cell == SPRITE && sprite->sx == -1))
	{
		if (inter->hit_side == VERT)
			put_vertical_element_coord(inter, wall, sprite);
		else
			put_horizontal_element_coord(inter, wall, sprite);
		if (inter->cell == 1 || inter->cell == CLOSE_DOOR)
			return (1);
	}
	return (0);
}

// ray casting 하는 함수
void	get_wall_intersection(t_var *var, double ray, \
								t_wall *wall, t_sprite *sprite)
{
	t_intersection	inter;

	init_intersection(var, &inter, ray);
	get_slope(&inter, ray);
	while (!inter.hit)
	{
		get_next_distance(&inter);
		get_map_coordinate(&inter);
		inter.cell = map_get_cell(&var->game, inter.mapx, inter.mapy);
		if (inter.cell < 0)
			break ;
		if (inter.cell == CLOSE_DOOR || inter.cell == OPEN_DOOR)
			wall->door = inter.cell;
		if (put_element_coordinate(&inter, wall, sprite))
			inter.hit = 1;
		if (inter.hit_side == VERT)
			inter.nx += inter.xstep;
		else
			inter.ny += inter.ystep;
	}
}

// 보고있는 벽의 좌표를 받아와 벽까지의 길이 구해주는 함수
void	cast_single_ray(t_var *var, int x, t_wall *wall, t_sprite *sprite)
{
	double	ray;
	double	dist;

	ray = (var->game.angle + fov_h_2()) - (x * angle_per_pixel());
	get_wall_intersection(var, ray, wall, sprite);
	dist = get_dist(var->game.px, var->game.py, wall->wx, wall->wy);
	wall->wdist = dist * cos(var->game.angle - ray);
	dist = get_dist(var->game.px, var->game.py, wall->dx, wall->dy);
	wall->ddist = dist * cos(var->game.angle - ray);
	dist = get_dist(var->game.px, var->game.py, sprite->sx, sprite->sy);
	sprite->sdist = dist * cos(var->game.angle - ray);
}

void	ray_casting(t_var *var, t_wall *wall, t_sprite *sprite)
{
	int		x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		init_ray_casting(&wall[x], &sprite[x]);
		cast_single_ray(var, x, &wall[x], &sprite[x]);
		if (x >= SCREEN_WIDTH / 2 - 10 && x <= SCREEN_WIDTH / 2 + 10)
			handling_door(var, &wall[x]);
		if (wall[x].wdir == DIR_WEST || wall[x].wdir == DIR_EAST)
			wall[x].wtx = (int)((wall[x].wy - floor(wall[x].wy)) * 64);
		else
			wall[x].wtx = (int)((wall[x].wx - floor(wall[x].wx)) * 64);
		if (sprite[x].sdir == DIR_WEST || sprite[x].sdir == DIR_EAST)
			sprite[x].stx = (int)((sprite[x].sy - floor(sprite[x].sy)) * 64);
		else
			sprite[x].stx = (int)((sprite[x].sx - floor(sprite[x].sx)) * 64);
		draw_wall(var, &wall[x], x);
		if (sprite[x].sx != -1)
			draw_sprite(var, &sprite[x], x);
		draw_line(&var->image, var->game.m_py, var->game.m_px, wall[x].wy * \
			(double)PIXEL_SIZE, wall[x].wx * (double)PIXEL_SIZE, RAY_COLOR);
	}
}
