/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finisher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:24:14 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:15:07 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_error(int errno, char *level, char *err)
{
	printf("%s: %s\n", level, err);
	return (errno);
}

int 	close_window(t_var *var)
{
	printf("end game\n");
	free_memory(var, 3);
	exit(0);
}