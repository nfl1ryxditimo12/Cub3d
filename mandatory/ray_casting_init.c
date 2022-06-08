/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:52:44 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:05:38 by seonkim          ###   ########.fr       */
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
