/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:26:14 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 20:34:35 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_init(t_var *var)
{
	var->image.image = mlx_new_image(var->mlx, SCREEN_WIDTH + \
						var->game.map_width * PIXEL_SIZE + 10, SCREEN_HEIGHT);
	var->image.addr = (int *)mlx_get_data_addr(var->image.image, \
		&var->image.bit_per_pixel, &var->image.size_line, &var->image.endian);
}

void	mlx_image_put(t_var *var)
{
	mlx_put_image_to_window(var->mlx, var->win, var->image.image, 0, 0);
	mlx_string_put(var->mlx, var->win, 30, var->game.map_height * \
					PIXEL_SIZE + 50, 0xFFFFFF, "Player move   : W, A, S, D");
	mlx_string_put(var->mlx, var->win, 30, var->game.map_height * \
					PIXEL_SIZE + 80, 0xFFFFFF, "Player rotate : <- , ->");
	mlx_string_put(var->mlx, var->win, 30, var->game.map_height * \
					PIXEL_SIZE + 110, 0xFFFFFF, "Interaction   : Space bar");
}

int	main_loop(t_var *var)
{
	clock_t	ms;

	ms = clock();
	if (!(ms % 30))
		var->rand = (rand() % 6) + 5;
	mlx_destroy_image(var->mlx, var->image.image);
	image_init(var);
	draw_game(var);
	mlx_image_put(var);
	mlx_hook(var->win, X_EVENT_KEY_PRESS, 0, &deal_key, var);
	mlx_hook(var->win, X_EVENT_KEY_EXIT, 0, &close_window, var);
	return (0);
}

int	cub3d_init(t_var *var, char *filename)
{
	int		errno;

	var->open = 0;
	var->mlx = mlx_init();
	errno = parse_cub3d_data(var, filename);
	if (errno)
	{
		free_memory(var, errno);
		return (1);
	}
	errno = check_valid_map(var);
	if (errno)
	{
		free_memory(var, errno);
		return (1);
	}
	image_init(var);
	var->win = mlx_new_window(var->mlx, SCREEN_WIDTH + 10 + \
				var->game.map_width * PIXEL_SIZE, SCREEN_HEIGHT, "Cub3D");
	var->rand = 5;
	return (0);
}
