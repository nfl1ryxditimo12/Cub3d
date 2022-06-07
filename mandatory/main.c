/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:01:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SCREEN_WIDTH-1.);
static const double FOVH_2 = FOV_H / 2.0;


// static int wall_colors[] = {    /* DIR_N, E, W, S */
//         0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
//     };


void image_init(t_var *var)
{
	var->image.image = mlx_new_image(var->mlx, SCREEN_WIDTH + var->game.map_width * PIXEL_SIZE + 10, SCREEN_HEIGHT);
	var->image.addr = (int *)mlx_get_data_addr(var->image.image, &var->image.bit_per_pixel,
										&var->image.size_line, &var->image.endian);
}

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

int
sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double
l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

int
map_get_cell(t_game *game, int x, int y )
{
    return (x >= 0 && x < game->map_height && y >= 0 && y < game->map_width) ? game->map[x][y] : -1;
}

t_bool
get_wall_intersection(t_var *var, double ray, t_dir* wdir, t_wall_pos *wall, t_sprite_pos *sprite)
{
	double px = var->game.px;
	double py = var->game.py;

    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    // printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
        // rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

    double f=INFINITY, g=INFINITY;
    t_bool hit = false;
    int hit_side; /* either VERT or HORIZ */

    while( !hit )
    {
        int mapx, mapy;

        if( xstep != 0 ) f = xslope * (nx-px) + py;
        if( ystep != 0 ) g = yslope * (ny-py) + px;

        /* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
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
        int cell = map_get_cell(&var->game, mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 || cell == SPRITE ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_WEST : DIR_EAST;
				if (cell == 1) {
					wall->wx = nx;
					wall->wy = f;
				} else {
					sprite->sx = nx;
					sprite->sy = f;
				}
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_SOUTH : DIR_NORTH;
				if (cell == 1) {
					wall->wx = g;
					wall->wy = ny;
				} else {
					sprite->sx = g;
					sprite->sy = ny;
				}
            }
            hit = true;
            // printf(" hit wall!\n");
            break;
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

void	cast_single_ray(t_var *var, int x, t_dir *wdir, t_wall_pos *wall, t_sprite_pos *sprite)
{
    double ray = (var->game.angle + FOVH_2) - (x * ANGLE_PER_PIXEL);

    get_wall_intersection(var, ray, wdir, wall, sprite);
        // return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(var->game.px, var->game.py, wall->wx, wall->wy);
	wall->wdist = wdist * cos(var->game.angle - ray);
	double sdist = l2dist(var->game.px, var->game.py, sprite->sx, sprite->sy);
	sprite->sdist = sdist * cos(var->game.angle - ray);
}

int
get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SCREEN_HEIGHT * (WALL_H / fov_h)); /* in pixels */
}

double get_luminosity(t_var *var, double dist)
{
	static double lum = -1;
	if (lum < 0) lum = (double)(var->game.map_width + var->game.map_height) / 2.0;
	return (dist > lum) ? 0 : (1. - dist / lum);
}

int	encode_color(int r, int g, int b)
{
	int color = 0;

	color += r;
	color = (color << 8);
	color += g;
	color = (color << 8);
	color += b;
	return color;
}

void decode_color(int color, int *r, int *g, int *b)
{
	*r = color & 0x00ff0000;
	*r = *r >> 16;
	*g = color & 0x0000ff00;
	*g = *g >> 8;
	*b = color & 0x000000ff;
}

int fade_color(int color, double lum)
{
	if (lum < 0) lum = 0;
	else if (lum > 1) lum = 1;
	int r, g, b;
	decode_color(color, &r, &g, &b);
	int new_color = encode_color((int)(r * lum), (int)(g * lum), (int)(b * lum));
	return new_color;
}

// void	draw_wall_line(t_image *image, double x1, double y1, double x2, double y2, int color)
// {
// 	double	deltaX;
// 	double	deltaY;
// 	double	step;

// 	deltaX = x2 - x1;
// 	deltaY = y2 - y1;
// 	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
// 	deltaX /= step;
// 	deltaY /= step;
// 	while (fabs(x2 - x1) > 1 || fabs(y2 - y1) > 1)
// 	{
// 		image->addr[(int)round(y1) * image->size_line / 4 + (int)round(x1)] = color;
// 		x1 += deltaX;
// 		y1 += deltaY;
// 	}
// }

double get_fov_min_dist()
{
	double T = -1;
	if (T < 0)
		T = WALL_H / (2.0 * tan(FOV_V / 2.0));
	return T;
}

void draw_sprite(t_var *var, t_sprite_pos *sprite, int x)
{
	int sh = get_wall_height(sprite->sdist);
	int y0 = (int)((SCREEN_HEIGHT - sh)/2.0);
    int y1 = y0 + sh - 1;
	double lum = get_luminosity(var, sprite->sdist);

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SCREEN_HEIGHT-1, y1);

	for (int y = ystart; y <= yend; y++) {
		int ty = (int)((double)(y - y0) * 64 / sh);
		int color = var->texture[DIR_SPRITE].texture_image[64 * ty + (int)floor(sprite->sx)];
		if (color != 0) {
			color = fade_color(color, lum);
			var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = color;
		}
    	// draw_line(&var->image, x + 10 + var->game.map_width * PIXEL_SIZE, y, x + 10 + var->game.map_width * PIXEL_SIZE, yend, color);
	}
}

void
draw_wall(t_var *var, double wdist, int x, int tx, t_dir wdir)
{
    int wh = get_wall_height(wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((SCREEN_HEIGHT - wh)/2.0);
    int y1 = y0 + wh - 1;
	double lum = get_luminosity(var, wdist);

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SCREEN_HEIGHT-1, y1);

	// draw_line(&var->image, x + 10 + var->game.map_width * PIXEL_SIZE, 0, x + 10 + var->game.map_width * PIXEL_SIZE, ystart - 1, var->image.ceilling_color);
	// draw_line(&var->image, x + 10 + var->game.map_width * PIXEL_SIZE, yend + 1, x + 10 + var->game.map_width * PIXEL_SIZE, SCREEN_HEIGHT, var->image.floor_color);
	// for (int y = 0; y < ystart; y++)
	// 	var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = var->image.ceilling_color;
	// for (int y = yend + 1; y < SCREEN_HEIGHT; y++)
	// 	var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = var->image.floor_color;

	for (int y = ystart; y <= yend; y++) {
		int ty = (int)((double)(y - y0) * 64 / wh);
		int color = var->texture[wdir].texture_image[64 * ty + tx];
		color = fade_color(color, lum);
		var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = color;
    	// draw_line(&var->image, x + 10 + var->game.map_width * PIXEL_SIZE, y, x + 10 + var->game.map_width * PIXEL_SIZE, yend, color);
	}

	if (y1 < SCREEN_HEIGHT - 1)
	{
		double ec = get_fov_min_dist();

		for (int y = y1 + 1; y < SCREEN_HEIGHT; y++)
		{
			double h = (double)(SCREEN_HEIGHT - 1 - y) / SCREEN_HEIGHT;
            double D = ec / (1. - 2 * h);
            double lum_f = get_luminosity(var, D) - 0.2;

			var->image.addr[y * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = fade_color(var->image.ceilling_color, lum_f);
			var->image.addr[(SCREEN_HEIGHT - 1 -y) * var->image.size_line / 4 + (x + 10 + var->game.map_width * PIXEL_SIZE)] = fade_color(var->image.floor_color, lum_f);
		}
	}
}

/***********************************************************/

void 	draw_lines(t_var *var)
{
	int		i;
	int		j;
	// double k;

	i = 0;
	while (i < var->game.map_width)
	{
		draw_line(&var->image, i * PIXEL_SIZE, 0, i * PIXEL_SIZE, var->game.map_height * PIXEL_SIZE, GRID_COLOR);
		i++;
	}
	draw_line(&var->image, var->game.map_width * PIXEL_SIZE - 1, 0, var->game.map_width * PIXEL_SIZE - 1, var->game.map_height * PIXEL_SIZE, GRID_COLOR);
	j = 0;
	while (j < var->game.map_height)
	{
		draw_line(&var->image, 0, j * PIXEL_SIZE, var->game.map_width * PIXEL_SIZE, j * PIXEL_SIZE, GRID_COLOR);
		j++;
	}
	draw_line(&var->image, 0, var->game.map_height * PIXEL_SIZE - 1, var->game.map_width * PIXEL_SIZE, var->game.map_height * PIXEL_SIZE - 1, GRID_COLOR);
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
			var->image.addr[(y + i) * var->image.size_line / 4 + x + j] = color;
		}
	}
}

void	draw_rectangles(t_var *var)
{
	int i;
	int j;

	i = -1;
	while (++i < var->game.map_height)
	{
		j = -1;
		while (++j < var->game.map_width)
		{
			if (var->game.map[i][j] == WALL)
				draw_rectangle(var, j, i, WALL_COLOR);
			else if (var->game.map[i][j] == FLOOR)
				draw_rectangle(var, j, i, FLOOR_COLOR);
			else if (var->game.map[i][j] == SPRITE)
				draw_rectangle(var, j, i, SPRITE_COLOR);
		}
	}

}

void	draw_mini_map(t_var *var)
{
	draw_rectangles(var);
	// draw_lines(var);
	// for (int i = 0; i < 10; i++)
	// 	draw_line(&var->image, i + (var->game.map_width * PIXEL_SIZE), 0, i + (var->game.map_width * PIXEL_SIZE), (double)SCREEN_HEIGHT, 0xFFFFFF);
}
/**********************************************************/

int main_loop(t_var *var)
{
	t_wall_pos		wall_pos[SCREEN_WIDTH];
	t_sprite_pos	sprite_pos[SCREEN_WIDTH];

	mlx_destroy_image(var->mlx, var->image.image);
	image_init(var);

	// 미니맵 그리는곳 (격자, 칸)
	draw_mini_map(var);

	// Ray casting
	for( int x=0; x<SCREEN_WIDTH; x++ ) {
        t_dir		wdir;
        cast_single_ray(var, x, &wdir, &wall_pos[x], &sprite_pos[x]);
		double text_ratio = (wdir == DIR_WEST || wdir == DIR_EAST) ? (wall_pos[x].wy - floor(wall_pos[x].wy)) : (wall_pos[x].wx - floor(wall_pos[x].wx));
		// double sprite_ratio = sprite_pos[x].sx - floor(sprite_pos[x].)
		int	tx = (int)(text_ratio * var->texture[wdir].texture_width);

		// int color = var->texture[wdir].texture_image[(int)(64.0 * wall_pos[x].wx) + (int)wall_pos[x].];
		// double lum = get_luminosity(var, wdist);
		// color = fade_color(color, lum);
        draw_wall(var, wall_pos[x].wdist, x, tx, wdir);
		draw_sprite(var, &sprite_pos[x], x);
		draw_line(&var->image, var->game.m_py, var->game.m_px, wall_pos[x].wy * (double)PIXEL_SIZE, wall_pos[x].wx * (double)PIXEL_SIZE, RAY_COLOR);
    }

	// Player position
	double k = -1;
	double l;
	while (++k < var->game.map_height * PIXEL_SIZE)
	{
		l = -1;
		while (++l < var->game.map_width * PIXEL_SIZE)
			if (l >= var->game.m_py - 3 && l <= var->game.m_py + 3 && k >= var->game.m_px - 3 && k <= var->game.m_px + 3) {
				// printf("%lf %lf %lf %lf\n", var->game.px, var->game.py, var->game.m_px, var->game.m_py);

				var->image.addr[(int)(k * var->image.size_line / 4) + (int)l] = PLAYER_COLOR;
			}
	}
	// 쓸모없는 부분 (이미지 렌더링 테스트용)
	// for (int i = 0; i < var->texture->texture_height; i++) {
	// 	for (int j = 0; j < var->texture->texture_width; j++) {
	// 		var->image.addr[(i * var->image.size_line / 4 + MAPX * PIXEL_SIZE) + j] = var->texture[2].texture_image[i * var->texture->texture_height + j];
	// 	}
	// }

	mlx_put_image_to_window(var->mlx, var->win, var->image.image, 0, 0);

	return (0);
}

static int
get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
        default: /* invalid */
            return -1;
    }
    return 0;
}

int
player_move(t_game* game, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(game->angle, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = game->px + dx;
    ny = game->py + dy;

    if( map_get_cell(game, (int)nx, (int)ny) != 0 ) {
        printf("** bump !\n");
        return -1;
    }
    game->px = nx;
    game->py = ny;
	game->m_px = game->m_px + (dx * (double)PIXEL_SIZE);
	game->m_py = game->m_py + (dy * (double)PIXEL_SIZE);

    return 0;
}

void
player_rotate(t_game* pp, double th )
{
    pp->angle += th;
    if( pp->angle < 0 ) pp->angle += _2PI;
    else if( pp->angle > _2PI ) pp->angle -= _2PI;
}

int		deal_key(int key_code, t_var *var)
{
	if(key_code == KEY_ESC ) {   /* quit */
		exit(0);
	}
	if( key_code == KEY_LEFT || key_code == KEY_RIGHT ) {
		player_rotate(&var->game, ROT_UNIT * (key_code ==KEY_LEFT ? 1 : -1));
	}
	else if( key_code == KEY_W || key_code == KEY_A || key_code == KEY_S || key_code == KEY_D ) {
		if( player_move(&var->game, key_code, MOVE_UNIT) == 0 ) {
		}
	}

	return (0);
}

int 	close_window(t_var *var)
{
	(void)var;
		exit(0);
}

void test(char *filename)
{
	t_var	var;

	var.mlx = mlx_init();
	if (parse_cub3d_data(&var, filename))
		return;
	check_valid_map(&var);
	image_init(&var);
	// 미니맵 10 x 10 으로 맞추는 설정 나중에 해야함
	var.win = mlx_new_window(var.mlx, SCREEN_WIDTH + 10 + var.game.map_width * PIXEL_SIZE, SCREEN_HEIGHT, "Cub3D");

	for (int i =0 ; i< var.game.map_height; i++) {
		for (int j = 0; var.game.map[i][j] != '\n' ; j++) {
			if (var.game.map[i][j] == 11)
				printf("%d ", var.game.map[i][j]);
			else
				printf("%d  ", var.game.map[i][j]);
		}
		printf("\n");
	}
	int color = 0xdc6400;
	int r;
	int g;
	int b;
	decode_color(color, &r, &g, &b);
	printf("%d %d %d %d %d\n", color, r, g, b, encode_color(r, g, b));
	color = 0xe11e00;
	decode_color(color, &r, &g, &b);
	printf("%d %d %d %d %d\n", color, r, g, b, encode_color(r, g, b));
	printf("[%d, %d] - [%d, %d]\n", var.image.floor_color, 0xdc6400, var.image.ceilling_color, 0xe11e00);
	mlx_put_image_to_window(var.mlx, var.win, var.image.image, 0, 0);

	mlx_hook(var.win, X_EVENT_KEY_PRESS, 0, &deal_key, &var);
	mlx_hook(var.win, X_EVENT_KEY_EXIT, 0, &close_window, &var);

	mlx_loop_hook(var.mlx, &main_loop, &var);
    mlx_loop(var.mlx);

}

int	main( int ac, char** av)
{
	// ac != 2일 때 종료
	(void)ac;

	test(av[1]);


    return 0;
}
