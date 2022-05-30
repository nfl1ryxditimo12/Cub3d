#include "cub3d.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SX - 1.);
static const double FOVH_2 = FOV_H / 2.0;
// static int flag = 0;

void	draw_render(t_image *image, int column, int height)
{
	int margin = (WALL_DEFAULT_HEIGHT - height) / 2;
	
	for (int i = 0; i < margin; i++)
		image->addr[i * image->size_line / 4 + column + (MAP_COL * PIXEL_SIZE) + 10] = 0x00FFFF;
	for(int i  = 0; i < height; i++)
	{
		image->addr[(margin + i) * image->size_line / 4 + column + (MAP_COL * PIXEL_SIZE) + 10] = 0xFF0000;
	}
	for (int i = 0; i < margin; i++)
		image->addr[(margin + height + i) * image->size_line / 4 + column + (MAP_COL * PIXEL_SIZE) + 10] = 0x00FF00;
}

int sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx * dx + dy * dy);
}

enum e_map map_get_cell(t_game *game, int x, int y )
{
    return (x >= 0 && x < MAP_COL && y >= 0 && y < MAP_ROW) ? game->map[y][x] : NOTHING;
}

bool	get_wall_intersection(t_var *var, double ray, double px, double py, dir_t *wdir, double *wx, double *wy)
{
	int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);


	double nx = (xstep > 0) ? floor(px) + 1 : ((xstep < 0) ? ceil(px) - 1 : px);
	double ny = (ystep > 0) ? floor(py) + 1 : ((ystep < 0) ? ceil(py) - 1 : py);

	// if (flag != 3) {
		// printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
			// rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);
		// printf("%lf %lf\n", px, py);
		// flag++;
	// }

	double f = INFINITY,  g = INFINITY;
	bool hit = false;
	int hit_side;
 
	while (!hit)
	{
		int mapx, mapy;

		if (xstep != 0) f = xslope * (nx - px) + py;
		if (ystep != 0) g = yslope * (ny - py) + px;

		double dist_v = l2dist(px, py, nx, f);
		double dist_h = l2dist(px, py, g, ny);

		if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
            mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
            mapy = (int) f;
            hit_side = VERT;
            // printf(" V(%d, %.2f) ->", mapx, f);
        }
		else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
            // printf(" H(%.2f, %d) ->", g, mapy);
        }

		enum e_map cell = map_get_cell(&var->game, mapx / PIXEL_SIZE, mapy / PIXEL_SIZE);
		if (cell == NOTHING || cell == EMPTY_SPACE)
			break;
		if( cell == WALL ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_W : DIR_E;
                *wx = nx;
                *wy = f;
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_S : DIR_N;
                *wx = g;
                *wy = ny;
            }
            hit = true;
            // printf(" hit wall!\n");
            break;
        }

		if (hit_side == VERT) nx += xstep;
		else ny += ystep;
	}

	return hit;
}

int		get_wall_height(double dist)
{
	double fov_h = 2.0 * dist * tan(FOV_V / 2.0);
	return (int)(HEIGHT * (WALL_H / fov_h));
}

void	draw_wall(t_image *image, double wdist, int x, int color)
{
	int wh = get_wall_height(wdist);

	int y0 = (int)((HEIGHT - wh) / 2.0);
	int y1 = y0 + wh - 1;

	int ystart = max(0, y0);
	int yend = min(WIDTH - 1, y1);

	draw_line(image, x + MAP_COL * PIXEL_SIZE + 10, ystart, x + MAP_COL * PIXEL_SIZE + 10, yend, color);
}

void	draw_rays(t_var *var)
{
	int wall_color[4] = {
		0xFFFF00, 0xFF00FF, 0x00FFFF, 0xAAAAAA
	};
	for (int x = 0; x < SX; x++) {
		double px = var->game.player_pos_x;
		double py = var->game.player_pos_y;
		double ray = (var->game.th + FOVH_2) - (x * ANGLE_PER_PIXEL);

		dir_t wdir;
		double wx, wy;

		if (get_wall_intersection(var, ray, px, py, &wdir, &wx, &wy) == false) {
			printf("out of map!!\n");
			break;

		}
	
		double wdist = l2dist(px, py, wx, wy);
		wdist *= cos(var->game.th - ray);
		draw_line(&var->map, px, py, wx, wy, DIR_COLOR);
		draw_wall(&var->map, wdist, SX - 1 - x, wall_color[wdir]);
	}
}

void	draw_rays1(t_var *var)
{
	double radian = (M_PI / 3) / (double)WIDTH;

	double m_cos = cos( 0);
	double m_sin = sin( 0);
	// printf("%lf, %lf, %lf\n", radian * WIDTH, m_cos, m_sin);
	double distance = 0.0;
	while (var->game.map[((int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE) - 1][((int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE) - 1] != WALL)
		distance += 0.5;

	int wall_pos_x = (int)round(var->game.player_pos_x + distance * m_cos);
	int wall_pos_y = (int)round(var->game.player_pos_y + distance * m_sin);
	// printf("%d, %d, %lf, %lf\n", wall_pos_x,wall_pos_y, var->game.player_pos_x, var->game.player_pos_y);

	double dx = fabs(wall_pos_x - var->game.player_pos_x);
	double dy = fabs(wall_pos_y - var->game.player_pos_y);

		int is_big_x = dx > dy ? 1 : 0;

	for (double i = 0.0; i < WIDTH; i += 1) {
		m_cos = cos((i - WIDTH / 2) * radian + var->angle);
		m_sin = sin((i - WIDTH / 2) * radian + var->angle);
		distance = 0.0;

		while (var->game.map[(int)round(var->game.player_pos_y + distance * m_sin) / PIXEL_SIZE ][ (int)round(var->game.player_pos_x + distance * m_cos) / PIXEL_SIZE] != WALL)
			distance += 0.2;
		// printf("%lf\n", r);

		draw_line(&var->map, var->game.player_pos_x, var->game.player_pos_y, var->game.player_pos_x + distance * m_cos, var->game.player_pos_y + distance * m_sin, DIR_COLOR);

		wall_pos_x = round(var->game.player_pos_x + distance * m_cos);
		wall_pos_y = round(var->game.player_pos_y + distance * m_sin);

		dx = fabs(wall_pos_x - var->game.player_pos_x) * 3;
		dy = fabs(wall_pos_y - var->game.player_pos_y) * 3;


		if (is_big_x)
		{
			int height = WALL_DEFAULT_HEIGHT - (int)dx - 100;
			draw_render(&var->map, (int)i, height);
		}
		else
		{
			int height = WALL_DEFAULT_HEIGHT - (int)dy - 100;
			draw_render(&var->map, (int)i, height);
		}
	}
}