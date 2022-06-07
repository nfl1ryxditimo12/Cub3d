/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:52:44 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 18:54:18 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_intersection(t_var *var, t_intersection *inter, double ray)
{
	inter->px = var->game.px;
	inter->py = var->game.py;
	inter->xstep = determin_angle(cos(ray));
	inter->ystep = determin_angle(sin(ray));
	inter->hit = 0;
	inter->func = INFINITY;
	inter->gunc = INFINITY;
}

void	init_ray_casting(t_wall *wall, t_sprite *sprite)
{
	wall->dx = -1;
	wall->dy = -1;
	wall->ddist = -1;
	wall->door = NOTHING;
	sprite->sx = -1;
	sprite->sy = -1;
	sprite->sdist = -1;
}
