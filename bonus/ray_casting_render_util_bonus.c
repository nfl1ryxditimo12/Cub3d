/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_render_util_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:59:04 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:56:30 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_zero(double d)
{
	return (fabs(d) < EPS);
}

//judge zero
int	determin_angle(double d)
{
	if (is_zero(d))
		return (0);
	if (d > 0)
		return (1);
	return (-1);
}

// return inner map elements by offset
int	map_get_cell(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map_height && y >= 0 && y < game->map_width)
		return (game->map[x][y]);
	return (-1);
}

// calculate wall height
int	get_wall_height(double dist)
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(fov_v() / 2.0);
	return ((int)(SCREEN_HEIGHT * (WALL_H / fov_h)));
}
