/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 06:11:35 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_line_size(t_map *line)
{
	int	len;

	len = 0;
	while (line[len] != '\n')
		len++;
	return len;
}

t_map	*resize_line(t_map *line, int max_size, int line_size)
{
	t_map	*dest;
	int		idx;

	dest = (t_map *)malloc(sizeof(t_map) * max_size + 1);
	if (!dest)
		return (NULL);
	idx = -1;
	while (++idx < line_size)
		dest[idx] = line[idx];
	idx--;
	while (++idx < max_size)
		dest[idx] = EMPTY_SPACE;
	dest[idx] = '\n';
	free(line);
	return (dest);
}

int	resize_map(t_var *var)
{
	t_map	*ptr;
	int	line_size;
	int row;

	row = -1;
	while (++row < var->game.map_height)
	{
		line_size = get_line_size(var->game.map[row]);
		if (line_size == var->game.map_width)
			continue ;
		ptr = var->game.map[row];
		var->game.map[row] = resize_line(ptr, var->game.map_width, line_size);
		if (!var->game.map[row])
			return (3);
	}
	return (0);
}

int	check_around_elements(t_var *var, int row, int col, int flag)
{
	int result;

	result = 0;
	if (!flag || row < 0 || row == var->game.map_height ||
		col < 0 || col == var->game.map_width)
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
	return (elem == NORTH || elem == SOUTH ||
			elem == WEST || elem == EAST);
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
			if (var->game.map[row][col] == NOTHING ||
				(var->game.map[row][col] == EMPTY_SPACE &&
				check_around_elements(var, row, col, 2)))
				return (3);
			if (is_player_element(var->game.map[row][col]))
				player_pos += set_player_pos(var, row, col);
		}
	}
	if (player_pos != 1)
		return (3);
	return (0);
}

void	substitution_wall(t_var *var, int row, int col)
{
	if (row < 0 || row == var->game.map_height ||
		col < 0 || col == var->game.map_width)
		return ;
	if (var->game.map[row][col] != WALL)
		return ;
	var->game.map[row][col] = 11;
	substitution_wall(var, row - 1, col);
	substitution_wall(var, row + 1, col);
	substitution_wall(var, row, col - 1);
	substitution_wall(var, row, col + 1);
}

void	restore_wall(t_var *var, int row, int col)
{
	if (row < 0 || row == var->game.map_height ||
		col < 0 || col == var->game.map_width)
		return ;
	if (var->game.map[row][col] != 11)
		return ;
	var->game.map[row][col] = WALL;
	restore_wall(var, row - 1, col);
	restore_wall(var, row + 1, col);
	restore_wall(var, row, col - 1);
	restore_wall(var, row, col + 1);
}

int	check_double_map(t_var *var)
{
	int row;
	int col;

	row = -1;
	while (++row < var->game.map_height)
	{
		col = var->game.map_width - 1;
		while (col >= 0 && var->game.map[row][col] == EMPTY_SPACE)
			col--;
		if (col < 0 || var->game.map[row][col] != 11)
			return (1);
		col = 0;
		while (col < var->game.map_width && var->game.map[row][col] == EMPTY_SPACE)
			col++;
		if (col == var->game.map_width || var->game.map[row][col] != 11)
			return (1);
	}
	col = -1;
	while (++col < var->game.map_width)
	{
		row = var->game.map_height - 1;
		while (row >= 0 && var->game.map[row][col] == EMPTY_SPACE)
			row--;
		if (row < 0 || var->game.map[row][col] != 11)
			return (1);
		row = 0;
		while (row < var->game.map_height && var->game.map[row][col] == EMPTY_SPACE)
			row++;
		if (row == var->game.map_height || var->game.map[row][col] != 11)
			return (1);
	}
	return (0);
}

int	check_valid_wall(t_var *var)
{
	int	idx;

	idx = 0;
	while (var->game.map[0][idx] != WALL)
		idx++;
	substitution_wall(var, 0, idx);
	for (int i =0 ; i< var->game.map_height; i++) {
		for (int j = 0; var->game.map[i][j] != '\n' ; j++) {
			if (var->game.map[i][j] == 11)
				printf("%d ", var->game.map[i][j]);
			else
				printf("%d  ", var->game.map[i][j]);
		}
		printf("\n");
	}
	if (check_double_map(var))
		return (3);
	restore_wall(var, 0, idx);
	return (0);
}

int	check_valid_map(t_var *var)
{
	if (resize_map(var))
		printf("Error: Resize map\n"); // 이부분 에러 반환 처리
	if (check_valid_wall(var))
		printf("Error: Invalid map\n");
	if (check_valid_element(var))
		printf("Error: Empty space\n");
	printf("\n");
	return (0);
}
