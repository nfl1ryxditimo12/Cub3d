#include "cub3d.h"

int get_move_offset(double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? -1 : 1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? -1 : 1) * M_PI_2);
            break;
        default: /* invalid */
            return -1;
    }
    return 0;
}

void	player_rotate(t_game *game, double rotate)
{
	game->th += rotate;
	if (game->th < 0)
		game->th += (M_PI * 2.0);
	else if (game->th > (M_PI * 2.0))
		game->th -= (M_PI * 2.0);
}

int		player_move(t_game *game, int key, double amt)
{
	double dx = 0, dy = 0;
	double nx, ny;

	if (get_move_offset(game->th, key, amt, &dx, &dy) < 0) {
		fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
	}
	nx = game->player_pos_x + dx;
	ny = game->player_pos_y + dy;

	// printf("%d %d\n")
	if(map_get_cell(game, (int)nx / PIXEL_SIZE, (int)ny / PIXEL_SIZE) != SPACE) {
        printf("** bump !\n");
        return -1;
    }
    game->player_pos_x = nx;
    game->player_pos_y = ny;
    return 0;
}

int		deal_key(int key_code, t_var *var)
{
	// int px = (int)var->game.player_pos_x;
	// int py = (int)var->game.player_pos_y;
	// printf("%d %d\n", px, py);
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W || key_code == KEY_S || key_code == KEY_A || key_code == KEY_D)
		player_move(&var->game, key_code, MOVE_UNIT);
	else if (key_code == KEY_LEFT)
		player_rotate(&var->game, -ROT_UNIT);
	else if (key_code == KEY_RIGHT)
		player_rotate(&var->game, ROT_UNIT);

	return (0);
}

int 	close(t_var *var)
{
	(void)var;
		exit(0);
}