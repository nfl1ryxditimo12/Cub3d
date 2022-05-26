#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code

#define KEY_ESC			53
#define KEY_W			13
#define KEY_S			1
#define KEY_A			0
#define KEY_D			2
#define KEY_LEFT		123
#define KEY_RIGHT		124

# define TILE_SIZE 32
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE

# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

# define PI    3.14159265359

# define PLAYER_COLOR	0xFF0000
# define WALL_COLOR		0x333333
# define SPACE_COLOR	0x999999
# define GRID_COLOR		0xb3b3b3
# define DIR_COLOR		0xFFFF66

double px = 144, py = 176;
double angle;
double delX;
double delY;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct s_vec2
{
	double x;
	double y;
}				t_vec2;

typedef struct	s_game1
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_vec2	dir_vec;

	int		map[ROWS][COLS];
}				t_game1;


void    draw_dir_ray(t_game1 *game, double angle)
{
    double    ray_x;
    double    ray_y;
    double    dx;
    double    dy;
    double    max_value;

    ray_x = px;
    ray_y = py;

    dx = cos(angle) * game->dir_vec.x - sin(angle) * game->dir_vec.y;
    dy = sin(angle) * game->dir_vec.x + cos(angle) * game->dir_vec.y;

    max_value = fmax(fabs(dx), fabs(dy));
    dx /= max_value;
    dy /= max_value;
    while (1)
    {
        if (game->img.data[(int)floor(ray_y) * game->img.size_l / 4 + (int)floor(ray_x)] != 0x0000FF)
            game->img.data[(int)floor(ray_y) * game->img.size_l / 4 + (int)floor(ray_x)] = 0xFF0000;
        else
            break;
        ray_x += dx;
        ray_y += dy;
    }
}

void    draw_ray(t_game1 *game)
{
    double angle;

    angle = 0;
    while (angle < PI/6)
    {
        draw_dir_ray(game, angle);
        draw_dir_ray(game, -angle);
        angle += PI/72;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void    rotate_matrix(t_vec2 *vec, double angle)
{
    double    tmp_x;

    tmp_x = cos(angle) * vec->x - sin(angle) * vec->y;
    vec->y = sin(angle) * vec->x + cos(angle) * vec->y;
    vec->x = tmp_x;
}

// =====================================================

int		deal_key(int key_code, t_game1 *game)
{
	(void)game;
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		py -= 4;
	else if (key_code == KEY_S)
		py += 4;
	else if (key_code == KEY_LEFT)
		angle -= 0.1;
	else if (key_code == KEY_RIGHT)
		angle += 0.1;
	else if (key_code == KEY_A)
		px -= 4;
	else if (key_code == KEY_D)
		px += 4;

	return (0);
}

int 	close(t_game1 *game)
{
	(void)game;
		exit(0);
}

void	game_init(t_game1 *game)
{
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

void	window_init(t_game1 *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "mlx 42");
}

void	image_init(t_game1 *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

void	draw_line(t_game1 *game, double x1, double y1, double x2, double y2, int color)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 1 || fabs(y2 - y1) > 1)
	{
		int idx = (int)round(y1) * game->img.size_l / 4 + (int)round(x1);
		game->img.data[idx] = color;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_game1 *game)
{
	int		i;
	int		j;
	// double k;

	i = 0;
	while (i < COLS)
	{
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT, GRID_COLOR);
		i++;
	}
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT, GRID_COLOR);
	j = 0;
	while (j < ROWS)
	{
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE, GRID_COLOR);
		j++;
	}
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1, GRID_COLOR);
}
// void	draw_lines(t_game1 *game)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < COLS)
// 		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
// 	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
// 	j = 0;
// 	while (j < ROWS)
// 	{
// 		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
// 		j++;
// 	}
// 	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
// }

void	draw_rectangle(t_game1 *game, int x, int y, int color)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			// if (j == 0 || j == TILE_SIZE - 1 || i == 0 || i == TILE_SIZE - 1)
			// 	game->img.data[(y + i) * game->img.size_l / 4 + x + j] = 0xb3b3b3;
			// else
			game->img.data[(y + i) * game->img.size_l / 4 + x + j] = color;
		}
	}
}

void	draw_rectangles(t_game1 *game)
{
	int i;
	int j;

	i = -1;
	while (++i < ROWS)
	{
		j = -1;
		while (++j < COLS)
		{
			if (game->map[i][j] == 1)
				draw_rectangle(game, j, i, WALL_COLOR);
			else
				draw_rectangle(game, j, i, SPACE_COLOR);
		}
	}

}

void	draw_rays(t_game1 *game)
{
	for (double i = 7; i <=9; i += 0.03) {
		double m_cos = cos(PI / 4 * i + angle);
		double m_sin = sin(PI / 4 * i + angle);
		double r = 0;
		while (game->map[ (int)round(py + r * m_sin) / TILE_SIZE ][ (int)round(px + r * m_cos) / TILE_SIZE ] != 1)
		{
			r += 0.5;
		}
		// printf("%lf\n", r);

		draw_line(game, px, py, px + r * m_cos, py + r * m_sin, DIR_COLOR);
	}
}

int		main_loop(t_game1 *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	image_init(game);
	draw_rectangles(game);
	draw_lines(game);

	double k;
	double l;
	k = -1;
	while (++k < HEIGHT)
	{
		l = -1;
		while (++l < WIDTH)
			if (k >= py - 2 && k <= py + 2 && l >= px - 2 && l <= px + 2)
				game->img.data[(int)(k * game->img.size_l / 4) + (int)l] = PLAYER_COLOR;
	}

	draw_rays(game);
	// draw_ray(game);

	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int main()
{
	angle = 0;
	delX = cos(angle) * 5;
	delY = sin(angle) * 5;
	t_game1	game;
	game.dir_vec.x = 0;
	game.dir_vec.y = 0;
	game_init(&game);
	window_init(&game);
	image_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close, &game);

	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}
