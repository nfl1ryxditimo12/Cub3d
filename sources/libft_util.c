/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:42:30 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:14:24 by seonkim          ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return (1);
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	int		idx;

	dest = (char *)ft_alloc(ft_str_len(str) + 1);
	if (!str)
		return (NULL);
	idx = -1;
	while (str[++idx])
		dest[idx] = str[idx];
	dest[idx] = '\0';
	return (dest);
}

int ft_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}