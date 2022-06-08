/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_intersection_util.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:51:08 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:07:56 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_slope(t_intersection *inter, double ray)
{
	inter->xslope = INFINITY;
	inter->yslope = INFINITY;
	if (inter->xstep == 0)
		inter->nx = inter->px;
	else
	{
		inter->xslope = tan(ray);
		if (inter->xstep > 0)
			inter->nx = floor(inter->px) + 1;
		else
			inter->nx = ceil(inter->px) - 1;
	}
	if (inter->ystep == 0)
		inter->ny = inter->py;
	else
	{
		inter->yslope = 1. / tan(ray);
		if (inter->ystep > 0)
			inter->ny = floor(inter->py) + 1;
		else
			inter->ny = ceil(inter->py) - 1;
	}
}

void	get_map_coordinate(t_intersection *inter)
{
	if (inter->dist_v < inter->dist_h)
	{
		if (inter->xstep == 1)
			inter->mapx = (int)inter->nx;
		else
			inter->mapx = (int)(inter->nx - 1);
		inter->mapy = (int)inter->func;
		inter->hit_side = VERT;
	}
	else
	{
		inter->mapx = (int)inter->gunc;
		if (inter->ystep == 1)
			inter->mapy = (int)inter->ny;
		else
			inter->mapy = (int)(inter->ny - 1);
		inter->hit_side = HORIZ;
	}
}

void	get_next_distance(t_intersection *inter)
{
	if (inter->xstep != 0)
		inter->func = inter->xslope * (inter->nx - inter->px) + inter->py;
	if (inter->ystep != 0)
		inter->gunc = inter->yslope * (inter->ny - inter->py) + inter->px;
	inter->dist_v = get_dist(inter->px, inter->py, inter->nx, inter->func);
	inter->dist_h = get_dist(inter->px, inter->py, inter->gunc, inter->ny);
}

void	put_vertical_element_coord(t_intersection *inter, t_wall *wall)
{
	if (inter->xstep > 0)
		wall->wdir = DIR_WEST;
	else
		wall->wdir = DIR_EAST;
	wall->wx = inter->nx;
	wall->wy = inter->func;
}

void	put_horizontal_element_coord(t_intersection *inter, t_wall *wall)
{
	if (inter->ystep > 0)
		wall->wdir = DIR_SOUTH;
	else
		wall->wdir = DIR_NORTH;
	wall->wx = inter->gunc;
	wall->wy = inter->ny;
}
