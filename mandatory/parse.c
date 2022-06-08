/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:16:50 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/08 16:33:55 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(t_var *var, char *buffer)
{
	char	*filename;

	filename = get_filename(buffer);
	if (!ft_strcmp(buffer, IDENTIFIER_NORTH))
		return (load_texture(var->mlx, &var->texture[0], filename));
	else if (!ft_strcmp(buffer, IDENTIFIER_SOUTH))
		return (load_texture(var->mlx, &var->texture[1], filename));
	else if (!ft_strcmp(buffer, IDENTIFIER_WEST))
		return (load_texture(var->mlx, &var->texture[2], filename));
	else if (!ft_strcmp(buffer, IDENTIFIER_EAST))
		return (load_texture(var->mlx, &var->texture[3], filename));
	else if (!ft_strcmp(buffer, IDENTIFIER_FLOOR))
		return (load_color(&var->image.floor_color, filename));
	else if (!ft_strcmp(buffer, IDENTIFIER_CEILLING))
		return (load_color(&var->image.ceilling_color, filename));
	free(filename);
	return (0);
}

int	check_essential_elements(t_var *var, char **buffer)
{
	int	flag;
	int	idx;

	flag = 0;
	var->texture = (t_texture *)ft_alloc(sizeof(t_texture) * 4);
	idx = -1;
	while (++idx < 4)
		var->texture[idx].texture_image = NULL;
	while (**buffer && flag != ESSENTIAL_ELEMENTS)
	{
		while (**buffer == 32 || **buffer == 9)
			(*buffer)++;
		flag += set_texture(var, *buffer);
		*buffer += get_line_size(*buffer);
	}
	if (flag != ESSENTIAL_ELEMENTS)
		return (parse_error(2, ERROR_LEVEL, NOT_ENOUGH_ELEMENT));
	return (0);
}

int	parse_map_data(t_var *var, char *buffer)
{
	int	row;
	int	col;
	int	line_size;

	while (is_empty_line(buffer))
		buffer += get_line_size(buffer);
	var->game.map_height = get_map_size(buffer);
	if (var->game.map_height == 0)
		return (parse_error(2, ERROR_LEVEL, INVALID_MAP));
	var->game.map = (t_map **)ft_alloc(sizeof(t_map *) * \
										var->game.map_height + 1);
	row = -1;
	var->game.map_width = 0;
	while (++row < var->game.map_height)
	{
		line_size = get_line_size(buffer);
		var->game.map_width = ft_max(line_size - 1, var->game.map_width);
		var->game.map[row] = (t_map *)ft_alloc(sizeof(t_map) * line_size + 1);
		col = -1;
		while (++col < line_size)
			insert_map_data(&var->game.map[row][col], *buffer++);
		var->game.map[row][col] = '\n';
	}
	var->game.map[row] = NULL;
	return (0);
}

int	parse_cub3d_data(t_var *var, char *filename)
{
	char	*buffer;
	int		errno;

	if (check_file_extension(filename, MAP_FILE_EXTENSION))
		return (parse_error(1, ERROR_LEVEL, INVALID_FILENAME));
	buffer = read_file(filename);
	if (!buffer)
		return (parse_error(1, ERROR_LEVEL, INVALID_FILEDATA));
	errno = check_essential_elements(var, &buffer);
	if (errno)
		return (errno);
	errno = parse_map_data(var, buffer);
	if (errno)
		return (errno);
	return (0);
}
