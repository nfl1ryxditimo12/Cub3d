#include "init.h"

int main()
{
	t_mlx mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 500, 500, "test");
	mlx_loop(mlx.mlx);
	return (0);
}