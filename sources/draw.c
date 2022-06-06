/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:35:12 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:45:17 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// sprite, door등 여러 요소들 미니맵에 표시해주는 함수
void	draw_object(t_var *var)
{
	int i;
	int j;

	i = -1;
	while (++i < var->game.map_height)
	{
		j = -1;
		while (++j < var->game.map_width)
		{
			if (var->game.map[i][j] == SPRITE)
				draw_rectangle(var, j, i, SPRITE_COLOR);
			else if (var->game.map[i][j] == OPEN_DOOR || var->game.map[i][j] == CLOSE_DOOR)
				draw_rectangle(var, j, i, DOOR_COLOR);
		}
	}
}

// 위와 동일
void	draw_mini_map(t_var *var)
{
	draw_rectangles(var);
	for (int i = 0; i < 10; i++)
		draw_line(&var->image, i + (var->game.map_width * PIXEL_SIZE), 0, i + (var->game.map_width * PIXEL_SIZE), (double)SCREEN_HEIGHT, 0xFFFFFF);
}

void	draw_player(t_var *var)
{
	double i;
	double j;

	i = -1;
	while (++i < var->game.map_height * PIXEL_SIZE)
	{
		j = -1;
		while (++j < var->game.map_width * PIXEL_SIZE)
			if (j >= var->game.m_py - 3 && j <= var->game.m_py + 3 && i >= var->game.m_px - 3 && i <= var->game.m_px + 3)
				var->image.addr[(int)(i * var->image.size_line / 4) + (int)j] = PLAYER_COLOR;
	}
}

void	draw_game(t_var *var)
{
	t_wall		wall[SCREEN_WIDTH];
	t_sprite	sprite[SCREEN_WIDTH];

	draw_mini_map(var);
	ray_casting(var, wall, sprite);
	draw_object(var);
	draw_player(var);
}