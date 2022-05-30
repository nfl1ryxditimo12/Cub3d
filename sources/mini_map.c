#include "cub3d.h"

void	draw_line(t_image *image, double x1, double y1, double x2, double y2, int color)
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
		image->addr[(int)round(y1) * image->size_line / 4 + (int)round(x1)] = color;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_var *var)
{
	int		i;
	int		j;
	// double k;

	i = 0;
	while (i < MAP_COL)
	{
		draw_line(&var->map, i * PIXEL_SIZE, 0, i * PIXEL_SIZE, MAP_ROW * PIXEL_SIZE, GRID_COLOR);
		i++;
	}
	draw_line(&var->map, MAP_COL * PIXEL_SIZE - 1, 0, MAP_COL * PIXEL_SIZE - 1, MAP_ROW * PIXEL_SIZE, GRID_COLOR);
	j = 0;
	while (j < MAP_ROW)
	{
		draw_line(&var->map, 0, j * PIXEL_SIZE, MAP_COL * PIXEL_SIZE, j * PIXEL_SIZE, GRID_COLOR);
		j++;
	}
	draw_line(&var->map, 0, MAP_ROW * PIXEL_SIZE - 1, MAP_COL * PIXEL_SIZE, MAP_ROW * PIXEL_SIZE - 1, GRID_COLOR);
}

void	draw_rectangle(t_var *var, int x, int y, int color)
{
	int i;
	int j;

	x *= PIXEL_SIZE;
	y *= PIXEL_SIZE;
	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
		{
			// if (j == 0 || j == PIXEL_SIZE - 1 || i == 0 || i == PIXEL_SIZE - 1)
			// 	game->img.data[(y + i) * game->img.size_l / 4 + x + j] = 0xb3b3b3;
			// else
			var->map.addr[(y + i) * var->map.size_line / 4 + x + j] = color;
		}
	}
}

void	draw_rectangles(t_var *var)
{
	int i;
	int j;

	i = -1;
	while (++i < MAP_ROW)
	{
		j = -1;
		while (++j < MAP_COL)
		{
			if (var->game.map[i][j] == WALL)
				draw_rectangle(var, j, i, WALL_COLOR);
			else
				draw_rectangle(var, j, i, SPACE_COLOR);
		}
	}

}

void	draw_mini_map(t_var *var)
{
	draw_rectangles(var);
	draw_lines(var);
	for (int i = 0; i < 10; i++)
		draw_line(&var->map, i + (MAP_COL * PIXEL_SIZE), 0, i + (MAP_COL * PIXEL_SIZE), (double)HEIGHT, 0xFFFFFF);
}