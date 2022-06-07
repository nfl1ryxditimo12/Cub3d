/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:35:12 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:00:58 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_object(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	while (++i < var->game.map_height)
	{
		j = -1;
		while (++j < var->game.map_width)
		{
			if (var->game.map[i][j] == SPRITE)
				draw_rectangle(var, j, i, SPRITE_COLOR);
			else if (var->game.map[i][j] == OPEN_DOOR \
					|| var->game.map[i][j] == CLOSE_DOOR)
				draw_rectangle(var, j, i, DOOR_COLOR);
		}
	}
}

void	draw_mini_map(t_var *var)
{
	int			i;
	t_offset	p1;
	t_offset	p2;

	i = -1;
	draw_rectangles(var);
	while (++i < 10)
	{
		p1.x = i + (var->game.map_width * PIXEL_SIZE);
		p1.y = 0;
		p2.x = i + (var->game.map_width * PIXEL_SIZE);
		p2.y = (double)SCREEN_HEIGHT;
		draw_line(&var->image, p1, p2, 0xFFFFFF);
	}
}

void	draw_player(t_var *var)
{
	double	i;
	double	j;

	i = -1;
	while (++i < var->game.map_height * PIXEL_SIZE)
	{
		j = -1;
		while (++j < var->game.map_width * PIXEL_SIZE)
			if (j >= var->game.m_py - 3 && j <= var->game.m_py + 3 && \
					i >= var->game.m_px - 3 && i <= var->game.m_px + 3)
				var->image.addr[(int)(i * var->image.size_line / 4) + (int)j] \
															= PLAYER_COLOR;
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
