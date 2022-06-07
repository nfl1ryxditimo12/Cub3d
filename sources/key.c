/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:32 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 20:45:31 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_move_offset(double th, int key, double *pdx, double *pdy)
{
	if (key == KEY_W)
	{
		*pdx = 1 * MOVE_UNIT * cos(th);
		*pdy = 1 * MOVE_UNIT * sin(th);
	}
	else if (key == KEY_S)
	{
		*pdx = -1 * MOVE_UNIT * cos(th);
		*pdy = -1 * MOVE_UNIT * sin(th);
	}
	else if (key == KEY_A)
	{
		*pdx = MOVE_UNIT * cos(th + 1 * M_PI_2);
		*pdy = MOVE_UNIT * sin(th + 1 * M_PI_2);
	}
	else if (key == KEY_D)
	{
		*pdx = MOVE_UNIT * cos(th + (-1) * M_PI_2);
		*pdy = MOVE_UNIT * sin(th + (-1) * M_PI_2);
	}
	else
		return (-1);
	return (0);
}

int	player_move(t_game *game, int key)
{
	double	dx;
	double	dy;
	double	nx;
	double	ny;
	int		cell;

	if (get_move_offset(game->angle, key, &dx, &dy) < 0)
		return (-1);
	nx = game->px + dx;
	ny = game->py + dy;
	cell = map_get_cell(game, (int)nx, (int)ny);
	if (cell != 0 && cell != OPEN_DOOR)
	{
		printf("bump wall!!\n");
		return (-1);
	}
	game->px = nx;
	game->py = ny;
	game->m_px = game->m_px + (dx * (double)PIXEL_SIZE);
	game->m_py = game->m_py + (dy * (double)PIXEL_SIZE);
	return (0);
}

// 플레이어 회전
void	player_rotate(t_game *pp, double th)
{
	pp->angle += th;
	if (pp->angle < 0)
		pp->angle += _2PI;
	else if (pp->angle > _2PI)
		pp->angle -= _2PI;
}

int	deal_key(int key_code, t_var *var)
{
	if (key_code == KEY_ESC)
		close_window(var);
	if (key_code == KEY_LEFT)
		player_rotate(&var->game, ROT_UNIT * 1);
	else if (key_code == KEY_RIGHT)
		player_rotate(&var->game, ROT_UNIT * -1);
	else if (key_code == KEY_W || key_code == KEY_A \
			|| key_code == KEY_S || key_code == KEY_D)
		player_move(&var->game, key_code);
	else if (key_code == KEY_SPACEBAR)
		var->open = 1;
	return (0);
}
