/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_util_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:43:52 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

char	*read_file(char *filename)
{
	char	temp[BUFFER_SIZE];
	char	*ptr;
	int		fd;
	ssize_t	state;

	fd = open(filename, O_RDONLY);
	if (fd < 1)
		return (NULL);
	state = read(fd, temp, BUFFER_SIZE);
	close(fd);
	if (state < 1)
		return (NULL);
	ptr = temp;
	return (ptr);
}

char	*get_filename(char *buffer)
{
	char	*dest;
	int		size;
	int		idx;

	while (*buffer != 32 && *buffer != 9)
		buffer++;
	while (*buffer == 32 || *buffer == 9)
		buffer++;
	size = get_line_size(buffer) - 1;
	dest = (char *)ft_alloc(size + 1);
	idx = -1;
	while (++idx < size)
		dest[idx] = buffer[idx];
	dest[idx] = '\0';
	return (dest);
}
