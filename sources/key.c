/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:32:32 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 18:38:06 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
        default: /* invalid */
            return -1;
    }
    return 0;
}

int	player_move(t_game* game, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(game->angle, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = game->px + dx;
    ny = game->py + dy;

	int cell = map_get_cell(game, (int)nx, (int)ny);
    if(cell != 0 && cell != OPEN_DOOR) {
        printf("** bump !\n");
        return -1;
    }
    game->px = nx;
    game->py = ny;
	game->m_px = game->m_px + (dx * (double)PIXEL_SIZE);
	game->m_py = game->m_py + (dy * (double)PIXEL_SIZE);

    return 0;
}

// 플레이어 회전
void	player_rotate(t_game* pp, double th )
{
    pp->angle += th;
    if( pp->angle < 0 ) pp->angle += _2PI;
    else if( pp->angle > _2PI ) pp->angle -= _2PI;
}

int		deal_key(int key_code, t_var *var)
{
	if (key_code == KEY_ESC)
		close_window(var);
	if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
		player_rotate(&var->game, ROT_UNIT * (key_code ==KEY_LEFT ? 1 : -1));
	else if( key_code == KEY_W || key_code == KEY_A || key_code == KEY_S || key_code == KEY_D ) {
		if( player_move(&var->game, key_code, MOVE_UNIT) == 0 ) {
		}
	}
	else if (key_code == KEY_SPACEBAR)
		var->open = 1;

	return (0);
}