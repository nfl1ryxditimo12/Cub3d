/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_resize_util_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:21:43 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_map_line_size(t_map *line)
{
	int	len;

	len = 0;
	while (line[len] != '\n')
		len++;
	return (len);
}

t_map	*resize_line(t_map *line, int max_size, int line_size)
{
	t_map	*dest;
	int		idx;

	dest = (t_map *)ft_alloc(sizeof(t_map) * max_size + 1);
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
