/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:12:27 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_newline(char **arr)
{
	int	size;

	if (!arr || !*arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}

int	until_next_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (str[len] != 32 && str[len] != 9))
		len++;
	return (len);
}

int	get_line_size(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}
