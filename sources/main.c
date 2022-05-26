#include "cub3d.h"

#define WIDTH		1600
#define HEIGHT		1000
#define PIXEL_SIZE	32
#define WALL_DEFAULT_HEIGHT	1000


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
	game->player_pos_x =144;
	game->player_pos_y = 176;
}

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

void	draw_rays(t_var *var)
{
	double radian = (M_PI / 2) / 1600.0;

	double m_cos = cos( 0);
	double m_sin = sin( 0);
	printf("%lf, %lf, %lf\n", radian * 1600, m_cos, m_sin);
	double distance = 0.0;
	while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
		distance += 0.5;
	
	int wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
	int wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
	printf("%d, %d, %lf, %lf\n", wall_pos_x,wall_pos_y, var->game.player_pos_x, var->game.player_pos_y);
	
	int dx = (int)fabs(wall_pos_x - var->game.player_pos_x);
	int dy = (int)fabs(wall_pos_y - var->game.player_pos_y);

	int is_big_x = dx > dy ? 1 : 0;


	for (double i = -800.0; i < 800.0; i += 1) {
		m_cos = cos(i * radian);
		m_sin = sin( i * radian);
		distance = 0.0;
		while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
			distance += 0.5;
		
		wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
		wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
		
		dx = (int)fabs(wall_pos_x - var->game.player_pos_x);
		dy = (int)fabs(wall_pos_y - var->game.player_pos_y);

		if (is_big_x)
		{
			int height = WALL_DEFAULT_HEIGHT - dx;
			draw_line(var, (int)i, height);
		}
		else
		{
			int height = WALL_DEFAULT_HEIGHT - dy;
			draw_line(var, (int)i, height);
		}

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