/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_render_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:59:04 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 18:54:23 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_zero(double d)
{
	return (fabs(d) < EPS);
}

// 0인지 판단하는 함수 (아마 왼각 오른각 구분하려고 사용하는걸로 알음)
int	determin_angle(double d)
{
	if (is_zero(d))
		return (0);
	if (d > 0)
		return (1);
	return (-1);
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

	fov_h = 2.0 * dist * tan(fov_v() / 2.0);
	return ((int)(SCREEN_HEIGHT * (WALL_H / fov_h)));
}
