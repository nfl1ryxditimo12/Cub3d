/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_math_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:39:54 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 20:57:24 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 0인지 판단하는 함수 (아마 왼각 오른각 구분하려고 사용하는걸로 알음)
int	sgn(double d)
{
	if (is_zero(d))
		return (0);
	if (d > 0)
		return (1);
	return (-1);
}

// 기울기 구하는 함수
double	l2dist(double x0, double y0, double x1, double y1)
{
	double	dx;
	double	dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

// 좌표로 맵 내부의 요소 반환하는 함수
int	map_get_cell(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map_height && y >= 0 && y < game->map_width)
		return (game->map[x][y]);
	return (-1);
}

// 세울 벽의 높이를 구해주는 함수
int	get_wall_height(double dist)
{
	double	fov_h;

	fov_h = 2.0 * dist * tan(FOV_V / 2.0);
	return ((int)(SCREEN_HEIGHT * (WALL_H / fov_h)));
}

// 모름이건ㅋ
double	get_fov_min_dist(void)
{
	double	t;

	t = -1;
	if (t < 0)
		t = WALL_H / (2.0 * tan(FOV_V / 2.0));
	return (t);
}
