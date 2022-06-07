/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_math_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:39:54 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 17:03:51 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 기울기 구하는 함수
double	get_dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

double	get_fov_min_dist(void)
{
	double	t;

	t = -1;
	if (t < 0)
		t = WALL_H / (2.0 * tan(fov_v() / 2.0));
	return (t);
}

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180.0);
}

double	radian_to_degree(double radian)
{
	return (radian * 180.0 / M_PI);
}

double	angle_per_pixel(void)
{
	return (degree_to_radian(FOV) / (SCREEN_WIDTH - 1.));
}
