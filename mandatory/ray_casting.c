/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:38:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/08 16:14:24 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_element_coordinate(t_intersection *inter, t_wall *wall)
{
	if (inter->cell == 1)
	{
		if (inter->hit_side == VERT)
			put_vertical_element_coord(inter, wall);
		else
			put_horizontal_element_coord(inter, wall);
		if (inter->cell == 1)
			return (1);
	}
	return (0);
}

void	get_wall_intersection(t_var *var, double ray, t_wall *wall)
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
		if (put_element_coordinate(&inter, wall))
			inter.hit = 1;
		if (inter.hit_side == VERT)
			inter.nx += inter.xstep;
		else
			inter.ny += inter.ystep;
	}
}

void	cast_single_ray(t_var *var, int x, t_wall *wall)
{
	double	ray;
	double	dist;

	ray = (var->game.angle + fov_h_2()) - (x * angle_per_pixel());
	get_wall_intersection(var, ray, wall);
	dist = get_dist(var->game.px, var->game.py, wall->wx, wall->wy);
	wall->wdist = dist * cos(var->game.angle - ray);
}

void	get_texture_x_coord(t_wall *wall)
{
	if (wall->wdir == DIR_WEST || wall->wdir == DIR_EAST)
		wall->wtx = (int)((wall->wy - floor(wall->wy)) * 64);
	else
		wall->wtx = (int)((wall->wx - floor(wall->wx)) * 64);
}

void	ray_casting(t_var *var, t_wall *wall)
{
	int			x;
	t_offset	p1;
	t_offset	p2;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		cast_single_ray(var, x, &wall[x]);
		get_texture_x_coord(&wall[x]);
		draw_wall(var, &wall[x], x);
		p1.x = var->game.m_py;
		p1.y = var->game.m_px;
		p2.x = wall[x].wy * (double)PIXEL_SIZE;
		p2.y = wall[x].wx * (double)PIXEL_SIZE;
	}
}
