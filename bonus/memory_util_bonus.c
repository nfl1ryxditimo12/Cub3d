/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:57:02 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	*ft_alloc(int size)
{
	void	*ptr;

	ptr = (void *)malloc(size);
	if (!ptr)
	{
		printf("%s: %s\n", ERROR_LEVEL, MEMORY_FAIL);
		exit(1);
	}
	return (ptr);
}

void	**ft_dalloc(int size)
{
	void	**ptr;

	ptr = (void **)malloc(size);
	if (!ptr)
	{
		printf("%s: %s\n", ERROR_LEVEL, MEMORY_FAIL);
		exit(1);
	}
	return (ptr);
}

void	free_memory(t_var *var, int errno)
{
	int	idx;

	if (errno >= 2)
	{
		idx = -1;
		while (var->texture && ++idx < ESSENTIAL_ELEMENTS - 2)
			if (var->texture[idx].texture_image)
				free(var->texture[idx].texture_image);
		if (var->texture)
			free(var->texture);
		idx = -1;
		if (errno == 3 && var->game.map)
		{
			while (++idx < var->game.map_height)
				if (var->game.map[idx])
					free(var->game.map[idx]);
			free(var->game.map);
		}
	}
}
