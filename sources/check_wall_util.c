/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:24:17 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 20:02:37 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	substitution_wall(t_var *var, int row, int col)
{
	if (row < 0 || row == var->game.map_height \
		|| col < 0 || col == var->game.map_width)
		return ;
	if (var->game.map[row][col] != WALL)
		return ;
	var->game.map[row][col] = 22;
	substitution_wall(var, row - 1, col);
	substitution_wall(var, row + 1, col);
	substitution_wall(var, row, col - 1);
	substitution_wall(var, row, col + 1);
}

void	restore_wall(t_var *var, int row, int col)
{
	if (row < 0 || row == var->game.map_height \
		|| col < 0 || col == var->game.map_width)
		return ;
	if (var->game.map[row][col] != 22)
		return ;
	var->game.map[row][col] = WALL;
	restore_wall(var, row - 1, col);
	restore_wall(var, row + 1, col);
	restore_wall(var, row, col - 1);
	restore_wall(var, row, col + 1);
}

int	check_double_map(t_var *var)
{
	int	row;
	int	col;

	row = -1;
	while (++row < var->game.map_height)
	{
		col = var->game.map_width - 1;
		while (col >= 0 && var->game.map[row][col] == EMPTY_SPACE)
			col--;
		if (col < 0 || var->game.map[row][col] != 22)
			return (1);
		col = 0;
		while (col < var->game.map_width && var->game.map[row][col] == EMPTY_SPACE)
			col++;
		if (col == var->game.map_width || var->game.map[row][col] != 22)
			return (1);
	}
	col = -1;
	while (++col < var->game.map_width)
	{
		row = var->game.map_height - 1;
		while (row >= 0 && var->game.map[row][col] == EMPTY_SPACE)
			row--;
		if (row < 0 || var->game.map[row][col] != 22)
			return (1);
		row = 0;
		while (row < var->game.map_height && var->game.map[row][col] == EMPTY_SPACE)
			row++;
		if (row == var->game.map_height || var->game.map[row][col] != 22)
			return (1);
	}
	return (0);
}
