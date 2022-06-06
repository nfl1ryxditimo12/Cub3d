/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:38:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 21:14:37 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SCREEN_WIDTH-1.);
static const double FOVH_2 = FOV_H / 2.0;

// ray casting 하는 함수
void	get_wall_intersection(t_var *var, double ray, \
								t_wall *wall, t_sprite *sprite)
{
	double	px;
	double	py;
	int		xstep;
	int		ystep;
	double	xslope;
	double	yslope;
	double	nx;
	double	ny;
	double	f;
	double	g;
	t_bool	hit;
	int		hit_side;
	double	dist_v;
	double	dist_h;
	int		mapx;
	int		mapy;
	int		cell;

	px = var->game.px;
	py = var->game.py;
	xstep = sgn(cos(ray));
	ystep = sgn(sin(ray));
	if (xstep == 0)
	{
		xslope = INFINITY;
		nx = px;
	}
	else
	{
		xslope = tan(ray);
		if (xstep > 0)
			nx = floor(px) + 1;
		else
			nx = ceil(px) - 1;
	}
	if (ystep == 0)
	{
		yslope = INFINITY;
		ny = py;
	}
	else
	{
		yslope = 1. / tan(ray);
		if (ystep > 0)
			ny = floor(py) + 1;
		else
			ny = ceil(py) - 1;
	}
	f = INFINITY;
	g = INFINITY;
	hit = false;
	while (!hit)
	{
		if (xstep != 0)
			f = xslope * (nx - px) + py;
		if (ystep != 0)
			g = yslope * (ny - py) + px;
		dist_v = l2dist(px, py, nx, f);
		dist_h = l2dist(px, py, g, ny);
		if (dist_v < dist_h)
		{
			if (xstep == 1)
				mapx = (int)nx;
			else
				mapx = (int)(nx - 1);
			mapy = (int)f;
			hit_side = VERT;
		}
		else
		{
			mapx = (int)g;
			if (ystep == 1)
				mapy = (int)ny;
			else
				mapy = (int)(ny - 1);
			hit_side = HORIZ;
		}
		cell = map_get_cell(&var->game, mapx, mapy);
		if (cell < 0)
			break ;
		if (cell == CLOSE_DOOR || cell == OPEN_DOOR)
			wall->door = cell;
		if (cell == 1 || cell == CLOSE_DOOR || cell == OPEN_DOOR \
			|| (cell == SPRITE && sprite->sx == -1))
		{
			if (hit_side == VERT)
			{
				if (xstep > 0)
					wall->wdir = DIR_WEST;
				else
					wall->wdir = DIR_EAST;
				wall->wx = nx;
				wall->wy = f;
				if (cell == SPRITE)
				{
					sprite->sx = nx;
					sprite->sy = f;
					sprite->sdir = wall->wdir;
				}
				if ((cell == CLOSE_DOOR || cell == OPEN_DOOR) && wall->dx == -1)
				{
					wall->dx = nx;
					wall->dy = f;
					wall->dmapx = mapx;
					wall->dmapy = mapy;
				}
			}
			else
			{
				if (ystep > 0)
					wall->wdir = DIR_SOUTH;
				else
					wall->wdir = DIR_NORTH;
				wall->wx = g;
				wall->wy = ny;
				if (cell == SPRITE)
				{
					sprite->sx = g;
					sprite->sy = ny;
					sprite->sdir = wall->wdir;
				}
				if ((cell == CLOSE_DOOR || cell == OPEN_DOOR) && wall->dx == -1)
				{
					wall->dx = g;
					wall->dy = ny;
					wall->dmapx = mapx;
					wall->dmapy = mapy;
				}
			}
			if (cell == 1 || cell == CLOSE_DOOR)
				hit = true;
		}
		if (hit_side == VERT)
			nx += xstep;
		else
			ny += ystep;
	}
}

// 보고있는 벽의 좌표를 받아와 벽까지의 길이 구해주는 함수
void	cast_single_ray(t_var *var, int x, t_wall *wall, t_sprite *sprite)
{
	double	ray;
	double	dist;

	ray = (var->game.angle + FOVH_2) - (x * ANGLE_PER_PIXEL);
	get_wall_intersection(var, ray, wall, sprite);
	dist = l2dist(var->game.px, var->game.py, wall->wx, wall->wy);
	wall->wdist = dist * cos(var->game.angle - ray);
	dist = l2dist(var->game.px, var->game.py, wall->dx, wall->dy);
	wall->ddist = dist * cos(var->game.angle - ray);
	dist = l2dist(var->game.px, var->game.py, sprite->sx, sprite->sy);
	sprite->sdist = dist * cos(var->game.angle - ray);
}

void	ray_casting(t_var *var, t_wall *wall, t_sprite *sprite)
{
	double	ratio;
	int		x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		wall[x].dx = -1;
		wall[x].dy = -1;
		wall[x].ddist = -1;
		wall[x].door = NOTHING;
		sprite[x].sx = -1;
		sprite[x].sy = -1;
		sprite[x].sdist = -1;
		cast_single_ray(var, x, &wall[x], &sprite[x]);
		if (x >= SCREEN_WIDTH / 2 - 10 && x <= SCREEN_WIDTH / 2 + 10)
			handling_door(var, &wall[x]);
		if (wall[x].wdir == DIR_WEST)
			ratio = wall[x].wy - floor(wall[x].wy);
		else
			ratio = wall[x].wx - floor(wall[x].wx);
		wall[x].wtx = (int)(ratio * 64);
		if (sprite[x].sdir == DIR_WEST)
			ratio = sprite[x].sy - floor(sprite[x].sy);
		else
			ratio = sprite[x].sx - floor(sprite[x].sx);
		sprite[x].stx = (int)(ratio * 64);
		draw_wall(var, &wall[x], x);
		if (sprite[x].sx != -1)
			draw_sprite(var, &sprite[x], x);
		draw_line(&var->image, var->game.m_py, var->game.m_px, wall[x].wy * \
			(double)PIXEL_SIZE, wall[x].wx * (double)PIXEL_SIZE, RAY_COLOR);
	}
}
