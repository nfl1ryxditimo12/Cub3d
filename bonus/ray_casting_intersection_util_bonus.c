/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_intersection_util_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:51:08 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	put_vertical_element_coord(t_intersection *inter, t_wall *wall, \
											t_sprite *sprite)
{
	if (inter->xstep > 0)
		wall->wdir = DIR_WEST;
	else
		wall->wdir = DIR_EAST;
	wall->wx = inter->nx;
	wall->wy = inter->func;
	if (inter->cell == SPRITE)
	{
		sprite->sx = inter->nx;
		sprite->sy = inter->func;
		sprite->sdir = wall->wdir;
	}
	if ((inter->cell == CLOSE_DOOR || inter->cell == OPEN_DOOR) \
									&& wall->dx == -1)
	{
		wall->dx = inter->nx;
		wall->dy = inter->func;
		wall->dmapx = inter->mapx;
		wall->dmapy = inter->mapy;
	}
}

void	put_horizontal_element_coord(t_intersection *inter, t_wall *wall, \
											t_sprite *sprite)
{
	if (inter->ystep > 0)
		wall->wdir = DIR_SOUTH;
	else
		wall->wdir = DIR_NORTH;
	wall->wx = inter->gunc;
	wall->wy = inter->ny;
	if (inter->cell == SPRITE)
	{
		sprite->sx = inter->gunc;
		sprite->sy = inter->ny;
		sprite->sdir = wall->wdir;
	}
	if ((inter->cell == CLOSE_DOOR || inter->cell == OPEN_DOOR) \
									&& wall->dx == -1)
	{
		wall->dx = inter->gunc;
		wall->dy = inter->ny;
		wall->dmapx = inter->mapx;
		wall->dmapy = inter->mapy;
	}
}
