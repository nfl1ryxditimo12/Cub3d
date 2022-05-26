#include "cub3d.h"

void	draw_render(t_image *image, int column, int height)
{
	int margin = (WALL_DEFAULT_HEIGHT - height) / 2;
	
	for(int i  = 0; i < height; i++)
	{
		image->addr[(margin + i) * image->size_line / 4 + column] = 0xFF0000;
	}
}

void	draw_rays(t_var *var)
{
	double radian = (M_PI / 3) / (double)WIDTH;

	double m_cos = cos( 0);
	double m_sin = sin( 0);
	printf("%lf, %lf, %lf\n", radian * WIDTH, m_cos, m_sin);
	double distance = 0.0;
	while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
		distance += 0.5;

	int wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
	int wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
	printf("%d, %d, %lf, %lf\n", wall_pos_x,wall_pos_y, var->game.player_pos_x, var->game.player_pos_y);

	double dx = fabs(wall_pos_x - var->game.player_pos_x);
	double dy = fabs(wall_pos_y - var->game.player_pos_y);

	int is_big_x = dx > dy ? 1 : 0;

	for (double i = 0.0; i < WIDTH; i += 1) {
		m_cos = cos((i - WIDTH/2) * radian + var->angle);
		m_sin = sin( (i - WIDTH/2) * radian + var->angle);
		distance = 0.0;
		while (var->game.map[(int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE ][ (int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE] != WALL)
			distance += 0.5;
		// printf("%lf\n", r);

		draw_line(&var->map, var->game.player_pos_x, var->game.player_pos_y, var->game.player_pos_x + distance * m_cos, var->game.player_pos_y + distance * m_sin, DIR_COLOR);
		double wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
		double wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
		
		dx = fabs(wall_pos_x - var->game.player_pos_x) * 2;
		dy = fabs(wall_pos_y - var->game.player_pos_y) * 2;


		if (is_big_x)
		{
			int height = WALL_DEFAULT_HEIGHT - (int)dx;
			draw_render(&var->render, (int)i, height);
		}
		else
		{
			int height = WALL_DEFAULT_HEIGHT - (int)dy;
			draw_render(&var->render, (int)i, height);
		}
	}
}