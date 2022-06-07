/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:11:35 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	resize_map(t_var *var)
{
	t_map	*ptr;
	int		line_size;
	int		row;

	row = -1;
	while (++row < var->game.map_height)
	{
		line_size = get_map_line_size(var->game.map[row]);
		if (line_size == var->game.map_width)
			continue ;
		ptr = var->game.map[row];
		var->game.map[row] = resize_line(ptr, var->game.map_width, line_size);
		if (!var->game.map[row])
			return (parse_error(3, ERROR_LEVEL, MEMORY_FAIL));
	}
	return (0);
}

int	check_valid_element(t_var *var)
{
	int	player_pos;
	int	row;
	int	col;

	player_pos = 0;
	row = -1;
	while (++row < var->game.map_height)
	{
		col = -1;
		while (++col < var->game.map_width)
		{
			if (var->game.map[row][col] == CLOSE_DOOR &&
				check_valid_door(var->game.map, row, col))
				return (parse_error(3, ERROR_LEVEL, INVALID_DOOR));
			if (var->game.map[row][col] == NOTHING ||
				(var->game.map[row][col] == EMPTY_SPACE &&
				check_around_elements(var, row, col, 2)))
				return (parse_error(3, ERROR_LEVEL, INVALID_ELEMENT));
			if (is_player_element(var->game.map[row][col]))
				player_pos += set_player_pos(var, row, col);
		}
	}
	if (player_pos != 1)
		return (parse_error(3, ERROR_LEVEL, INVALID_PLAYER));
	return (0);
}

int	check_valid_wall(t_var *var)
{
	int	idx;

	idx = 0;
	while (var->game.map[0][idx] != WALL)
		idx++;
	substitution_wall(var, 0, idx);
	if (check_double_map(var))
		return (parse_error(3, ERROR_LEVEL, DOUBLE_MAP));
	restore_wall(var, 0, idx);
	return (0);
}

int	check_valid_map(t_var *var)
{
	int	errno;

	errno = resize_map(var);
	if (errno)
		return (errno);
	errno = check_valid_wall(var);
	if (errno)
		return (errno);
	errno = check_valid_element(var);
	if (errno)
		return (errno);
	return (0);
}
