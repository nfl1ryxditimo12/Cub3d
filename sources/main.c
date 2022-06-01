/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:01:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/01 14:56:15 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SCREEN_WIDTH-1.);
static const double FOVH_2 = FOV_H / 2.0;


static int map[MAPX][MAPY] = {
		{8,8,8,8,8,8,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{8,8,8,8,8,8,8,8,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{8,8,8,8,8,8,8,8,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{8,8,8,8,8,8,8,8,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,8,8,8,8},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,8,8,8,8},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,8,8,8,8},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,1,8,8,8,8},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,8,8,8,8},
		{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,8,8},
		{1,1,1,1,0,1,1,1,8,1,1,1,0,1,0,1,8,1,0,1,1,1,1,0,1,0,0,0,1,8,8,8,8},
		{1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,1,1,1,8,8,8,8}
	};

static int wall_colors[] = {    /* DIR_N, E, W, S */
        0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
    };


void image_init(t_var *var)
{
	var->image.image = mlx_new_image(var->mlx, SCREEN_WIDTH + MAPY * PIXEL_SIZE + 10, SCREEN_HEIGHT);
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
map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

bool
get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    // printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
        // rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

    double f=INFINITY, g=INFINITY;
    bool hit = false;
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
        int cell = map_get_cell(mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 ) {   /* hit wall? */
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

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

double
cast_single_ray(t_var *var, int x, dir_t *wdir )
{
    double ray = (var->game.angle + FOVH_2) - (x * ANGLE_PER_PIXEL);

    double wx, wy;  /* coord. of wall intersection point */

    if( get_wall_intersection(ray, var->game.px, var->game.py, wdir, &wx, &wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(var->game.px, var->game.py, wx, wy);
	wdist *= cos(var->game.angle - ray);

	draw_line(&var->image, var->game.m_py, var->game.m_px, wy * (double)PIXEL_SIZE, wx * (double)PIXEL_SIZE, DIR_COLOR);
    return wdist;
}

int
get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SCREEN_HEIGHT * (WALL_H / fov_h)); /* in pixels */
}

void
draw_wall(t_var *var, double wdist, int x, int color )
{
    int wh = get_wall_height(wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((SCREEN_HEIGHT - wh)/2.0);
    int y1 = y0 + wh - 1;

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SCREEN_HEIGHT-1, y1);

    draw_line(&var->image, x + 10 + MAPY * PIXEL_SIZE, ystart, x + 10 + MAPY * PIXEL_SIZE, yend, color);
}

/***********************************************************/

void 	draw_lines(t_var *var)
{
	int		i;
	int		j;
	// double k;

	i = 0;
	while (i < MAPY)
	{
		draw_line(&var->image, i * PIXEL_SIZE, 0, i * PIXEL_SIZE, MAPX * PIXEL_SIZE, GRID_COLOR);
		i++;
	}
	draw_line(&var->image, MAPY * PIXEL_SIZE - 1, 0, MAPY * PIXEL_SIZE - 1, MAPX * PIXEL_SIZE, GRID_COLOR);
	j = 0;
	while (j < MAPX)
	{
		draw_line(&var->image, 0, j * PIXEL_SIZE, MAPY * PIXEL_SIZE, j * PIXEL_SIZE, GRID_COLOR);
		j++;
	}
	draw_line(&var->image, 0, MAPX * PIXEL_SIZE - 1, MAPY * PIXEL_SIZE, MAPX * PIXEL_SIZE - 1, GRID_COLOR);
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
	while (++i < MAPX)
	{
		j = -1;
		while (++j < MAPY)
		{
			if (map[i][j] == 1)
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
		draw_line(&var->image, i + (MAPY * PIXEL_SIZE), 0, i + (MAPY * PIXEL_SIZE), (double)SCREEN_HEIGHT, 0xFFFFFF);
}
/**********************************************************/

double get_luminosity(double dist)
{
	static double lum = -1;
	if (lum < 0) lum = (double)(MAPX + MAPY) / 2.0;
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
	*r = (color >> 16) & 0x0000FF;
	*g = (color >> 8) & 0x0000FF;
	*b = color & 0x0000FF;
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

int main_loop(t_var *var)
{
	mlx_destroy_image(var->mlx, var->image.image);
	image_init(var);
	draw_mini_map(var);
	double k = -1;
	double l;
	while (++k < MAPX * PIXEL_SIZE)
	{
		l = -1;
		while (++l < MAPY * PIXEL_SIZE)
			if (l >= var->game.m_py - 3.5 && l <= var->game.m_py + 3.5 && k >= var->game.m_px - 3.5 && k <= var->game.m_px + 3.5) {
				printf("%lf %lf %lf %lf\n", var->game.px, var->game.py, var->game.m_px, var->game.m_py);

				var->image.addr[(int)(k * var->image.size_line / 4) + (int)l] = PLAYER_COLOR;
			}
	}
	// for (double i = 0; i < MAPX; i += MOVE_UNIT) {
	// 	for (double j = 0; j < MAPY; j += MOVE_UNIT) {
	// 		if (i >= var->game.py - 0.1 && i <= var->game.py + 0.1 && j >= var->game.px - 0.1 && j <= var->game.px + 0.1) {

	// 			int px = (int)(i * (double)PIXEL_SIZE);
	// 			int py = (int)(j * (double)PIXEL_SIZE);
	// 			printf("%d %d\n", px, py);
	// 			var->image.addr[py * var->image.size_line / 4 + px] = PLAYER_COLOR;
	// 		}
	// 	}
	// }

	for( int x=0; x<SCREEN_WIDTH; x++ ) {
        dir_t wdir;
        double wdist = cast_single_ray(var, x, &wdir);
		int color = wall_colors[wdir];
		double lum = get_luminosity(wdist);
			color = fade_color(wall_colors[wdir], lum);
        draw_wall(var, wdist, x, color);
    }

	for (int i = 0; i < var->texture->texture_height; i++) {
		for (int j = 0; j < var->texture->texture_width; j++) {
			var->image.addr[(i * var->image.size_line / 4 + MAPX * PIXEL_SIZE) + j] = var->texture->texture_image[i * var->texture->texture_height + j];
		}
	}

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
player_move(t_game* pp, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(pp->angle, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = pp->px + dx;
    ny = pp->py + dy;

    if( map_get_cell((int)nx, (int)ny) != 0 ) {
        printf("** bump !\n");
        return -1;
    }
    pp->px = nx;
    pp->py = ny;
	pp->m_px = pp->m_px + (dx * (double)PIXEL_SIZE);
	pp->m_py = pp->m_py + (dy * (double)PIXEL_SIZE);

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
	// int px = (int)var->game.player_pos_x;
	// int py = (int)var->game.player_pos_y;
	// printf("%d %d\n", px, py);
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

// int 	close(t_var *var)
// {
// 	(void)var;
// 		exit(0);
// }

// void    load_image(t_var *var, t_texture *texture, char *path, t_image *image)
// {
//     image->image = mlx_xpm_file_to_image(var->mlx, path, &image->image_width, &image->image_height);
// 	if (image->image == NULL)
// 		printf("nononono\n");
//     image->addr = (int *)mlx_get_data_addr(image->image, &image->bit_per_pixel, &image->size_line, &image->endian);
// 	var->texture->texture_image = malloc(sizeof(int) * image->image_height * image->image_width);
//     for (int y = 0; y < image->image_height; y++)
//     {
//         for (int x = 0; x < image->image_width; x++)
//         {
//             texture->texture_image[image->image_width * y + x] = image->addr[image->image_width * y + x];
//         }
//     }
// 	texture->texture_height = image->image_height;
// 	texture->texture_width = image->image_width;
//     mlx_destroy_image(var->mlx, image->image);
// }

// void    load_texture(t_var *var)
// {
//     t_image    image;

// 	var->texture = malloc(sizeof(t_texture));
//     load_image(var, var->texture, "assets/eagle.xpm", &image);
// }

void test(char *filename)
{
	t_var	var;

	var.mlx = mlx_init();
	parse_cub3d_data(&var, filename);
	check_valid_map(&var);
	var.win = mlx_new_window(var.mlx, SCREEN_WIDTH + 10 + (var.game.map_width > 10 ? 10 : var.game.map_width) * PIXEL_SIZE, SCREEN_HEIGHT, "Cub3D");

	for (int i =0 ; i< var.game.map_height; i++) {
		for (int j = 0; var.game.map[i][j] != '\n' ; j++) {
			if (var.game.map[i][j] == 11)
				printf("%d ", var.game.map[i][j]);
			else
				printf("%d  ", var.game.map[i][j]);
		}
		printf("\n");
	}

	// mlx_hook(var.win, X_EVENT_KEY_PRESS, 0, &deal_key, &var);
	// mlx_hook(var.win, X_EVENT_KEY_EXIT, 0, &close, &var);
	
	// mlx_loop_hook(var.mlx, &main_loop, &var);
    mlx_loop(var.mlx);

}

int	main( int ac, char** av)
{

	// var.win = mlx_new_window(var.mlx, SCREEN_WIDTH + 10 + MAPY * PIXEL_SIZE, SCREEN_HEIGHT, "mlx");
	// image_init(&var);

    // if( ac != 4 ) {
    //     // fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
    //     exit(1);
	// }

	// load_texture(&var);
    
    // var.game.px = atof(av[1]);
    // var.game.py = atof(av[2]);
	// var.game.m_px = var.game.px * (double)(PIXEL_SIZE);
    // var.game.m_py = var.game.py * (double)(PIXEL_SIZE);
    // var.game.angle = deg2rad(atof(av[3]));

    // /* print map */
    // // for( int y=MAPY-1; y>=0; y-- ) {
    // //     for( int x=0; x<MAPX; x++ ) {
    // //         // printf("%c ", (map_get_cell(x,y)==1 ? '#':'.'));
    // //     }
    // //     putchar('\n');
    // // }

	// mlx_hook(var.win, X_EVENT_KEY_PRESS, 0, &deal_key, &var);
	// mlx_hook(var.win, X_EVENT_KEY_EXIT, 0, &close, &var);
	// mlx_loop_hook(var.mlx, &main_loop, &var);
    // mlx_loop(var.mlx);

	(void)ac;

	test(av[1]);


    return 0;
}