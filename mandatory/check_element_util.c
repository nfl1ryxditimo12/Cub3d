/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:25:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:01:22 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_around_elements(t_var *var, int row, int col, int flag)
{
	int	result;

	result = 0;
	if (!flag || row < 0 || row == var->game.map_height \
		|| col < 0 || col == var->game.map_width)
		return (0);
	result += check_around_elements(var, row - 1, col, flag - 1);
	result += check_around_elements(var, row + 1, col, flag - 1);
	result += check_around_elements(var, row, col - 1, flag - 1);
	result += check_around_elements(var, row, col + 1, flag - 1);
	result += check_around_elements(var, row - 1, col - 1, flag - 1);
	result += check_around_elements(var, row + 1, col - 1, flag - 1);
	result += check_around_elements(var, row - 1, col + 1, flag - 1);
	result += check_around_elements(var, row + 1, col + 1, flag - 1);
	if (var->game.map[row][col] != EMPTY_SPACE &&
		var->game.map[row][col] != WALL)
		return (1);
	return (result);
}

int	is_player_element(t_map elem)
{
	return (elem == NORTH || elem == SOUTH \
			|| elem == WEST || elem == EAST);
}

int	set_player_pos(t_var *var, int row, int col)
{
	var->game.px = (double)row + 0.5;
	var->game.py = (double)col + 0.5;
	var->game.m_px = var->game.px * (double)PIXEL_SIZE;
	var->game.m_py = var->game.py * (double)PIXEL_SIZE;
	if (var->game.map[row][col] == NORTH)
		var->game.angle = 200.0;
	else if (var->game.map[row][col] == SOUTH)
		var->game.angle = 360;
	else if (var->game.map[row][col] == WEST)
		var->game.angle = 90;
	else if (var->game.map[row][col] == EAST)
		var->game.angle = 270;
	var->game.map[row][col] = FLOOR;
	return (1);
}
