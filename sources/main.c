#include "cub3d.h"

void	window_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH + (MAP_COL * PIXEL_SIZE) + 10, HEIGHT, "Cub3D");
}

void	image_init(t_image *image, void *mlx, int width, int height)
{
	image->image = mlx_new_image(mlx, width, height);
	image->addr = (int *)mlx_get_data_addr(image->image, &image->bit_per_pixel,
										&image->size_line, &image->endian);
}

void	game_init(t_game *game)
{
	char map[11][15] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	game->map = (enum e_map **)malloc(sizeof(enum e_map *) * 11);
	for (int i = 0; i < 11; i++) {
		game->map[i] = (enum e_map *)malloc(sizeof(enum e_map) * 15);
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == '1')
				game->map[i][j] = WALL;
			else if (map[i][j] == '0')
				game->map[i][j] = SPACE;
			else if (map[i][j] == 'N')
				game->map[i][j] = NORTH;
		}
	}
	game->player_pos_x = 144;
	game->player_pos_y = 176;
}

void	var_init(t_var *var)
{
	var->angle = 0;
	window_init(&var->mlx);
	game_init(&var->game);
	image_init(&var->map, var->mlx.mlx, MAP_COL * PIXEL_SIZE, MAP_ROW * PIXEL_SIZE);
	image_init(&var->division, var->mlx.mlx, 10, HEIGHT);
	image_init(&var->render, var->mlx.mlx, WIDTH, HEIGHT);
}

// void	draw_render(t_image *image, int column, int height)
// {
// 	int margin = (WALL_DEFAULT_HEIGHT - height) / 2;
	
// 	for(int i  = 0; i < height; i++)
// 	{
// 		image->addr[(margin + i) * image->size_line + column * 4] = 0xFF0000;
// 	}
// }

// void	draw_renders(t_var *var)
// {
// 	double radian = (M_PI / 2) / 1600.0;

// 	double m_cos = cos( 0);
// 	double m_sin = sin( 0);
// 	double distance = 0.0;
// 	while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
// 		distance += 0.5;
	
// 	int wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
// 	int wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
	
// 	int dx = (int)fabs(wall_pos_x - var->game.player_pos_x);
// 	int dy = (int)fabs(wall_pos_y - var->game.player_pos_y);

// 	int is_big_x = dx > dy ? 1 : 0;


// 	for (double i = -800.0; i < 800.0; i += 1) {
// 		m_cos = cos(i * radian);
// 		m_sin = sin( i * radian);
// 		distance = 0.0;
// 		while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
// 			distance += 0.5;
		
// 		wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
// 		wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
		
// 		dx = (int)fabs(wall_pos_x - var->game.player_pos_x);
// 		dy = (int)fabs(wall_pos_y - var->game.player_pos_y);

// 		if (is_big_x)
// 		{
// 			int height = WALL_DEFAULT_HEIGHT - dx;
// 			draw_render(&var->render, (int)i, height);
// 		}
// 		else
// 		{
// 			int height = WALL_DEFAULT_HEIGHT - dy;
// 			draw_render(&var->render, (int)i, height);
// 		}

// 	}
// }

int	game_loop(t_var *var)
{
	mlx_destroy_image(var->mlx.mlx, var->map.image);
	mlx_destroy_image(var->mlx.mlx, var->division.image);
	mlx_destroy_image(var->mlx.mlx, var->render.image);
	image_init(&var->map, var->mlx.mlx, MAP_COL * PIXEL_SIZE, MAP_ROW * PIXEL_SIZE);
	image_init(&var->division, var->mlx.mlx, 10, HEIGHT);
	image_init(&var->render, var->mlx.mlx, WIDTH, HEIGHT);
	draw_mini_map(var);
	
	double k;
	double l;
	k = -1;
	while (++k < MAP_ROW * PIXEL_SIZE)
	{
		l = -1;
		while (++l < MAP_COL * PIXEL_SIZE)
			if (k >= var->game.player_pos_y - 2 && k <= var->game.player_pos_y + 2 && l >= var->game.player_pos_x - 2 && l <= var->game.player_pos_x + 2)
				var->map.addr[(int)(k * var->map.size_line / 4) + (int)l] = PLAYER_COLOR;
	}

	draw_rays(var);
	// draw_renders(var);
	mlx_put_image_to_window(var->mlx.mlx, var->mlx.win, var->map.image, 0, 0);
	mlx_put_image_to_window(var->mlx.mlx, var->mlx.win, var->division.image, MAP_COL * PIXEL_SIZE, 0);
	mlx_put_image_to_window(var->mlx.mlx, var->mlx.win, var->render.image, MAP_COL * PIXEL_SIZE + 10, 0);
	return (0);
}

int main()
{
	t_var	var;

	var_init(&var);

	mlx_hook(var.mlx.win, X_EVENT_KEY_PRESS, 0, &deal_key, &var);
	mlx_hook(var.mlx.win, X_EVENT_KEY_EXIT, 0, &close, &var);

	mlx_put_image_to_window(var.mlx.mlx, var.mlx.win, var.map.image, 0, 0);
	mlx_put_image_to_window(var.mlx.mlx, var.mlx.win, var.division.image, MAP_COL * PIXEL_SIZE, 0);
	mlx_put_image_to_window(var.mlx.mlx, var.mlx.win, var.render.image, MAP_COL * PIXEL_SIZE + 10, 0);
	mlx_loop_hook(var.mlx.mlx, &game_loop, &var);
	mlx_loop(var.mlx.mlx);
	return(0);
}