#include "cub3d.h"

int		deal_key(int key_code, t_var *var)
{
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		var->game.player_pos_y -= 4;
	else if (key_code == KEY_S)
		var->game.player_pos_y += 4;
	else if (key_code == KEY_LEFT)
		var->angle -= 0.1;
	else if (key_code == KEY_RIGHT)
		var->angle += 0.1;
	else if (key_code == KEY_A)
		var->game.player_pos_x -= 4;
	else if (key_code == KEY_D)
		var->game.player_pos_x += 4;

	return (0);
}

int 	close(t_var *var)
{
	(void)var;
		exit(0);
}