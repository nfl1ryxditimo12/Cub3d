/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:16:50 by seonkim           #+#    #+#             */
/*   Updated: 2022/05/31 21:58:12 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_str_len(char *str)
{
	int	len;

	if (!str || !*str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	check_newline(char **arr)
{
	int size;

	if (!arr || !*arr)
		return (0);
	while (arr[size])
		size++;
	return (size);
}


int	check_file_extension(char *filename, char *extension)
{
	int	file_len;
	int	idx;

	file_len = ft_str_len(filename);
	if (file_len <= 4)
		return (1);
	idx = file_len - ft_str_len(extension);
	if (filename[idx] == extension[0])
		if (filename[idx + 1] == extension[1])
			if (filename[idx + 2] == extension[2])
				if (filename[idx + 3] == extension[3])
					return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return (1);
	return (0);
}

int	read_file(char *filename, char *buffer)
{
	int		fd;
	ssize_t	state;

	fd = open(filename, O_RDONLY);
	if (fd < 1)
		return (1);
	state = read(fd, buffer, BUFFER_SIZE);
	close(fd);
	return ((int)state);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	int		idx;

	idx = 0;
	dest = (char *)malloc(ft_str_len(str) + 1);
	if (!str || !dest)
		return (NULL);
	while (str[idx])
		dest[idx] = str[idx];
	dest[idx] = NULL;
	return (dest);
}

int	until_next_space(char *str)
{
	int len;

	len = 0;
	while (str[len] && (str[len] != 32 || str[len] != 9))
		len++;
	return (len);
}


int		get_line_size(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	return len;
}

char	*get_filename(char *buffer)
{
	char	*dest;
	int		size;
	int		idx;

	while (*buffer != 32 || *buffer != 9)
		buffer++;
	while (*buffer == 32 || *buffer == 9)
		buffer++;
	size = get_line_size(buffer);
	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	idx = 0;
	while (idx < size)
		dest[idx] = buffer[idx];
	dest[idx] = NULL;
	return dest;
}

int	load_texture(void *mlx, t_texture *texture, char *filename)
{
	t_image	image;
	int		x;
	int		y;

	// 잘못된 image 경로 들어왔을 때 터지는거 확인해야함
	image.image = mlx_xpm_file_to_image(mlx, filename, &image.image_width, &image.image_height);
	texture->texture_image = malloc(sizeof(int) * image.image_width * image.image_height);
	if (!image.image || !texture->texture_image)
		return (0);
	image.addr = mlx_get_data_addr(image.image, &image.bit_per_pixel, &image.size_line, &image.endian);
	y = -1;
	while (++y < image.image_height)
    {
		x = -1;
        while (++x < image.image_width)
            texture->texture_image[image.image_width * y + x] = image.addr[image.image_width * y + x];
    }
	texture->texture_height = image.image_height;
	texture->texture_width = image.image_width;
    mlx_destroy_image(mlx, image.image);
	if (filename)
		free(filename);
	return (1);
}

int	check_essential_elements(t_var *var, char **buffer)
{
	int flag;

	flag = 0;
	var->texture = malloc(sizeof(t_texture) * 6);
	if (!var->texture)
		return (1);
	while (**buffer && flag != ESSENTIAL_ELEMENTS)
	{
		while (**buffer == 32 || **buffer == 9)
			*buffer++;
		if (!ft_strcmp(*buffer, IDENTIFIER_NORTH))
			flag += load_texture(var->mlx, &var->texture[0], get_filename(*buffer));
		else if (!ft_strcmp(*buffer, IDENTIFIER_SOUTH))
			flag += load_texture(var->mlx, &var->texture[1], get_filename(*buffer));
		else if (!ft_strcmp(*buffer, IDENTIFIER_WEST))
			flag += load_texture(var->mlx, &var->texture[2], get_filename(*buffer));
		else if (!ft_strcmp(*buffer, IDENTIFIER_EAST))
			flag += load_texture(var->mlx, &var->texture[3], get_filename(*buffer));
		else if (!ft_strcmp(*buffer, IDENTIFIER_FLOOR))
			flag += load_texture(var->mlx, &var->texture[4], get_filename(*buffer)); // 색으로 변경 필요
		else if (!ft_strcmp(*buffer, IDENTIFIER_CEILLING))
			flag += load_texture(var->mlx, &var->texture[5], get_filename(*buffer));
		*buffer += get_line_size(*buffer);
	}
	if (flag != ESSENTIAL_ELEMENTS)
		return (2);
	return (0);
}

int	is_empty_line(char *buffer)
{
	int	idx;

	idx = 0;
	while (buffer[idx] && buffer[idx] != '\n')
		if (buffer[idx] != 32 || buffer[idx++] != 9)
			return (0);
	return (1);
}

int	get_map_size(char *buffer)
{
	int	size;
	int	line_size;

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

int ft_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void	insert_map_data(t_map *line, char data)
{
	if (data == '0')
		*line = CEILLING;
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
		*line = DOOR;
	else if (data == 'M')
		*line = SPRITE;
	else if (data == ' ')
		*line = EMPTY_SPACE;
	else
		*line = NOTHING;
	return (0);
}

// 배열의 끝에 NULL을 넣어줄지 고민해봐야함
int	parse_map_data(t_var *var, char *buffer)
{
	int	row;
	int	col;
	int	line_size;

	while (is_empty_line(buffer))
		buffer += get_line_size(buffer);
	var->game.map_height = get_map_size(buffer);
	if (var->game.map_height == 0)
		return (1);
	var->game.map = (t_map **)malloc(sizeof(t_map *) * var->game.map_height);
	if (!var->game.map)
		return (1);
	row = -1;
	var->game.map_width = 0;
	while (++row < var->game.map_height)
	{
		line_size = get_line_size(buffer) - 1;
		var->game.map_width = ft_max(line_size, var->game.map_width);
		var->game.map[row] = (t_map *)malloc(sizeof(t_map) * line_size);
		if (!var->game.map[row])
			return (2);
		col = -1;
		while (++col < line_size)
			insert_map_data(&var->game.map[row][col], *buffer);
		buffer += line_size + 1;
	}
	return (0);
}

int	parse_cub3d_data(t_var *var, char *filename)
{
	char	*buffer;

	// 맵 파일 확장자가 이상한 경우 실패
	if (check_file_extension(filename, MAP_FILE_EXTENSION))
		return (1);
	// 파일을 못읽은 경우, 버퍼사이즈보다 파일이 큰 경우, 읽기 실패한 경우 실패
	if (read_file(filename, buffer))
		return (1);
	// 동적할당 실패한 경우, 필수 요소가 누락된 경우, 텍스쳐 파일 읽기 실패한 경우
	if (check_essential_elements(var, &buffer))
		return (1); // 실패시 동적 할당 해제 필요
	// 동적할당 실패한 경우, 맵 중간에 빈 줄이 있는 경우 실패
	if (parse_map_data(var, buffer))
		return (1);
}