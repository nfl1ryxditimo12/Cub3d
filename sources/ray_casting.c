/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:38:15 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:48:45 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const double ANGLE_PER_PIXEL = FOV_H / (SCREEN_WIDTH-1.);
static const double FOVH_2 = FOV_H / 2.0;

// ray casting 하는 함수
t_bool	get_wall_intersection(t_var *var, double ray, t_wall *wall, t_sprite *sprite)
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
		if (cell == CLOSE_DOOR || cell == OPEN_DOOR)
			wall->door = cell;
        if( cell == 1 || cell == CLOSE_DOOR || cell == OPEN_DOOR || (cell == SPRITE && sprite->sx == -1)) {   /* hit wall? */
            if( hit_side == VERT ) {
                wall->wdir = (xstep > 0) ? DIR_WEST : DIR_EAST;
			
				wall->wx = nx;
				wall->wy = f;
				if (cell == SPRITE) {
					sprite->sx = nx;
					sprite->sy = f;
					sprite->sdir = wall->wdir;
				}
				if ((cell == CLOSE_DOOR || cell == OPEN_DOOR) && wall->dx == -1) {
					wall->dx = nx;
					wall->dy = f;
					wall->dmapx = mapx;
					wall->dmapy = mapy;
				}
            }
            else { /* HORIZ */
                wall->wdir = (ystep > 0) ? DIR_SOUTH : DIR_NORTH;
				wall->wx = g;
				wall->wy = ny;
				
				if (cell == SPRITE) {
					sprite->sx = g;
					sprite->sy = ny;
					sprite->sdir = wall->wdir;
				}
				if ((cell == CLOSE_DOOR || cell == OPEN_DOOR) && wall->dx == -1) {
					wall->dx = g;
					wall->dy = ny;
					wall->dmapx = mapx;
					wall->dmapy = mapy;
				}
			}
			
			if (cell == 1 || cell == CLOSE_DOOR) {
				hit = true;
				// printf(" hit wall!\n");
				break;
			}
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

// 보고있는 벽의 좌표를 받아와 벽까지의 길이 구해주는 함수
void	cast_single_ray(t_var *var, int x, t_wall *wall, t_sprite *sprite)
{
    double ray = (var->game.angle + FOVH_2) - (x * ANGLE_PER_PIXEL);

    get_wall_intersection(var, ray, wall, sprite);
        // return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(var->game.px, var->game.py, wall->wx, wall->wy);
	wall->wdist = wdist * cos(var->game.angle - ray);
	double ddist = l2dist(var->game.px, var->game.py, wall->dx, wall->dy);
	wall->ddist = ddist * cos(var->game.angle - ray);
	double sdist = l2dist(var->game.px, var->game.py, sprite->sx, sprite->sy);
	sprite->sdist = sdist * cos(var->game.angle - ray);
}

void	ray_casting(t_var *var, t_wall *wall, t_sprite *sprite)
{
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		// 동적 할당으로 변경해야 함
		wall[x].dx = -1;
		wall[x].dy = -1;
		wall[x].ddist = -1;
		wall[x].door = NOTHING;
		sprite[x].sx = -1;
		sprite[x].sy = -1;
		sprite[x].sdist = -1;
        cast_single_ray(var, x, &wall[x], &sprite[x]);
		if (x >= SCREEN_WIDTH / 2 - 10 && x <= SCREEN_WIDTH / 2 + 10)
			handling_door(var, &wall[x]);
		// x쪽을 봐야하는지 y쪽을 봐야하는지 지정해주는 부분
		double text_ratio = (wall[x].wdir == DIR_WEST || wall[x].wdir == DIR_EAST) ? (wall[x].wy - floor(wall[x].wy)) : (wall[x].wx - floor(wall[x].wx));
		// 스프라이트와 벽 텍스쳐의 ray 하나 당 가로길이 지정해 주는 부분
		wall[x].wtx = (int)(text_ratio * var->texture[wall[x].wdir].texture_width);
		double sprite_ratio = (sprite[x].sdir == DIR_WEST || sprite[x].sdir == DIR_EAST) ? (sprite[x].sy - floor(sprite[x].sy)) : (sprite[x].sx - floor(sprite[x].sx));
		sprite[x].stx = (int)(sprite_ratio * 64);
        draw_wall(var, &wall[x], x);
		// sx가 -1인 경우 sprite가 아님
		if (sprite[x].sx != -1)
			draw_sprite(var, &sprite[x], x);
		draw_line(&var->image, var->game.m_py, var->game.m_px, wall[x].wy * (double)PIXEL_SIZE, wall[x].wx * (double)PIXEL_SIZE, RAY_COLOR);
    }
}