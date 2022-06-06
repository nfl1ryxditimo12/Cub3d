/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:08:09 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:14:18 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *buffer)
{
	int	idx;

	idx = 0;
	while (buffer[idx] && buffer[idx] != '\n')
	{
		if (buffer[idx] != 32 && buffer[idx] != 9)
			return (0);
		idx++;
	}
	return (1);
}

int	get_map_size(char *buffer)
{
	int	size;

	size = 0;
	while (*buffer)
	{
		if (is_empty_line(buffer))
			return (0);
		buffer += get_line_size(buffer);
		size++;
	}
	return (size);
}

void	insert_map_data(t_map *line, char data)
{
	if (data == '0')
		*line = FLOOR;
	else if (data == '1')
		*line = WALL;
	else if (data == 'N')
		*line = NORTH;
	else if (data == 'S')
		*line = SOUTH;
	else if (data == 'W')
		*line = WEST;
	else if (data == 'E')
		*line = EAST;
	else if (data == 'D')
		*line = CLOSE_DOOR;
	else if (data == 'O')
		*line = SPRITE;
	else if (data == ' ')
		*line = EMPTY_SPACE;
	else
		*line = NOTHING;
}