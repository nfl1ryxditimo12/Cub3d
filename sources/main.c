/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:01:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:52:55 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 문 열고 닫는 함수
void handling_door(t_var *var, t_wall *wall)
{
	if (wall->ddist > 1.5 || var->open == 0)
	{
		if (var->open == 1)
			var->open = 0;
		return ;
	}
	if (wall->door == CLOSE_DOOR)
		var->game.map[wall->dmapx][wall->dmapy] = OPEN_DOOR;
	else if (wall->door == OPEN_DOOR)
		var->game.map[wall->dmapx][wall->dmapy] = CLOSE_DOOR;
	var->open = 0;
}

void test(char *filename)
{
	t_var	var;
	
	if (cub3d_init(&var, filename))
		exit(1);
	mlx_put_image_to_window(var.mlx, var.win, var.image.image, 0, 0);
	mlx_loop_hook(var.mlx, &main_loop, &var);
    mlx_loop(var.mlx);
}

int	main( int ac, char** av)
{
	// ac != 2일 때 종료하게 해야함
	if (ac != 2)
		return (parse_error(1, ERROR_LEVEL, INVALID_FILENAME));
	test(av[1]);
	system("leaks cub3D | grep Process");
    return (0);
}