#include "cub3d.h"

#define WIDTH		1200
#define HEIGHT		800
#define PIXEL_SIZE	32
#define WALL_DEFAULT_HEIGHT	800
# define KEY_ESC		53
# define KEY_W			13
# define KEY_S			1
# define KEY_A			0
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define  ROT_UNIT   0.06    /* rad */
# define  MOVE_UNIT  0.15


void	window_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
}

void	image_init(t_var *var)
{
	var->image.image = mlx_new_image(var->mlx.mlx, WIDTH, HEIGHT);
	var->image.addr = mlx_get_data_addr(var->image.image, &var->image.bit_per_pixel,
										&var->image.size_line, &var->image.endian);
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
	game->player_pos_x = 4 * PIXEL_SIZE + PIXEL_SIZE /2;
	game->player_pos_y = 5 * PIXEL_SIZE + PIXEL_SIZE /2;
}

// void	game_init(t_game *game)
// {
// 	char map[14][33] = {
// 	{'9',  '9',  '9',  '9',  '9',  '9',  '9',  '9',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1'},
// 	{'9',  '9',  '9',  '9',  '9',  '9',  '9',  '9',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1'},
// 	{'9',  '9',  '9',  '9',  '9',  '9',  '9',  '9',  '1',  '0',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '7',  '0',  '0',  '0',  '0',  '1'},
// 	{'9',  '9',  '9',  '9',  '9',  '9',  '9',  '9',  '1',  '0',  '0',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1'},
// 	{'1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '0',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1'},
// 	{'1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1'},
// 	{'1',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '0',  '0',  '0',  '1',  '9',  '9',  '9',  '9'},
// 	{'1',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '0',  '1',  '0',  '1',  '0',  '0',  '1',  '0',  '0',  '0',  '1',  '9',  '9',  '9',  '9'},
// 	{'1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '0',  '1',  '0',  '1',  '0',  '1',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '0',  '0',  '0',  '1',  '9',  '9',  '9',  '9'},
// 	{'1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '0',  '0',  '0',  '1',  '9',  '9',  '9',  '9'},
// 	{'1',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '0',  '1',  '1',  '0',  '1',  '0',  '1',  '0',  '0',  '1',  '0',  '0',  '0',  '1',  '9',  '9',  '9',  '9'},
// 	{'1',  '1',  '0',  '0',  '0',  '0',  '1',  '1',  '1',  '1',  '0',  '1',  '0',  '1',  '0',  '1',  '1',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '1',  '0',  '0',  '0',  '1',  '1',  '1',  '9',  '9'},
// 	{'1',  '1',  '1',  '1',  '0',  '1',  '1',  '1',  '9',  '1',  '1',  '1',  '0',  '1',  '0',  '1',  '9',  '1',  '0',  '1',  '1',  '1',  '1',  '0',  '1',  '0',  '0',  '0',  '1',  '9',  '9',  '9',  '9'},
// 	{'1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '9',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '9',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '1',  '9',  '9',  '9',  '9'}
// 	};
// 	game->map = (enum e_map **)malloc(sizeof(enum e_map *) * 14);
// 	for (int i = 0; i < 14; i++) {
// 		game->map[i] = (enum e_map *)malloc(sizeof(enum e_map) * 33);
// 		for (int j = 0; j < 33; j++) {
// 			if (map[i][j] == '1')
// 				game->map[i][j] = WALL;
// 			else if (map[i][j] == '0')
// 				game->map[i][j] = SPACE;
// 			else if (map[i][j] == 'N')
// 				game->map[i][j] = NORTH;
// 		}
// 	}
// 	game->player_pos_x = 14 * PIXEL_SIZE + PIXEL_SIZE /2;
// 	game->player_pos_y = 4 * PIXEL_SIZE + PIXEL_SIZE /2;
// }

void	var_init(t_var *var)
{
	window_init(&var->mlx);
	game_init(&var->game);
	image_init(var);
}

void	draw_line(t_var *var, int column, int height)
{
	int margin = (WALL_DEFAULT_HEIGHT - height) / 2;

	for(int i  = 0; i < height; i++)
	{
		int *ptr = (int *)(var->image.addr + ((margin + i) * var->image.size_line + column * 4));
		*ptr = 0xFF0000;
	}
}

/**
 * origin
*/
// void	draw_rays(t_var *var)
// {
// 	double foh = (M_PI / 3) / (double)WIDTH;
// 	printf(" %lf\n", foh);


// 	double m_cos = cos(0);
// 	double m_sin = sin( 0);
// 	double distance = 0.0;
// 	while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
// 		distance += 0.5;

// 	int wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
// 	int wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
// 	printf("%d, %d, %lf, %lf\n", wall_pos_x,wall_pos_y, var->game.player_pos_x, var->game.player_pos_y);

// 	double dx = (int)fabs(wall_pos_x - var->game.player_pos_x);
// 	double dy = (int)fabs(wall_pos_y - var->game.player_pos_y);

// 	int is_big_x = dx > dy ? 1 : 0;


// 	for (double i = 0.0; i < WIDTH; i += 1) {
// 		double radian = (i - WIDTH/2) * foh;
// 		m_cos = cos(radian);
// 		m_sin = sin(radian);
// 		distance = 0.0;
// 		while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
// 			distance += 0.5;

// 		wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
// 		wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);

// 		dx = fabs(wall_pos_x - var->game.player_pos_x) / PIXEL_SIZE;
// 		dy = fabs(wall_pos_y - var->game.player_pos_y) / PIXEL_SIZE;
// 		printf("%lf, %lf\n", dx, dy);

// 		double height;
// 		double height2;

// 		if (is_big_x)
// 		{
// 			height = WALL_DEFAULT_HEIGHT / (dx/ 2 );
// 			height2 = (double)HEIGHT / (2 * dx * tan(M_PI / 9));
// 			if (height >= WALL_DEFAULT_HEIGHT)
// 				height = WALL_DEFAULT_HEIGHT;
// 		}
// 		else
// 		{
// 			height = WALL_DEFAULT_HEIGHT / (dy /2 );
// 			height2 =  (double)HEIGHT / (2 * dy * tan(M_PI / 9));
// 			if (height >= WALL_DEFAULT_HEIGHT)
// 				height = WALL_DEFAULT_HEIGHT;
// 		}
// 		printf("1 = %lf, 2 = %lf\n", height, height2);
// 		draw_line(var, (int)i, height);

// 	}
// }

void	draw_rays(t_var *var)
{
	double foh = (M_PI / 3) / (double)WIDTH;
	printf(" %lf\n", foh);

	// double pivot = M_PI / 2;
	double pivot = 0;

	for (double i = 0.0; i < WIDTH; i += 1) {
		double radian = (i - WIDTH/2) * foh + pivot;
		double m_cos = cos(radian);
		double m_sin = sin(radian);
		double distance = 0.0;
		while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
			distance += 0.5;

		// dx = fabs(wall_pos_x - var->game.player_pos_x) / PIXEL_SIZE;
		// dy = fabs(wall_pos_y - var->game.player_pos_y) / PIXEL_SIZE;
		// printf("%lf, %lf\n", dx, dy);
		double dx = distance * cos(pivot - radian) / (double)PIXEL_SIZE;
		double dy = distance * cos(pivot - radian) / (double)PIXEL_SIZE;
		printf("%lf, %lf\n", dx, dy);

		double height2;

		height2 = (double)HEIGHT / ((double)2 * dx * tan(M_PI / 9));
		if (height2 >= WALL_DEFAULT_HEIGHT)
			height2 = WALL_DEFAULT_HEIGHT;
		draw_line(var, (int)i, (int)round(height2));

	}
}

int	game_loop(t_var *var)
{
	mlx_destroy_image(var->mlx.mlx, var->image.image);
	image_init(var);

	draw_rays(var);
	mlx_put_image_to_window(var->mlx.mlx, var->mlx.win, var->image.image, 0, 0);
	return (0);
}

int main()
{
	t_var	var;

	var_init(&var);

	mlx_put_image_to_window(var.mlx.mlx, var.mlx.win, var.image.image, 0, 0);
	mlx_loop_hook(var.mlx.mlx, &game_loop, &var);
	mlx_loop(var.mlx.mlx);
	return(0);
}
