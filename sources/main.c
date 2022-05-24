#include "init.h"

typedef struct     s_data {
    void        *img;
    char        *addr;
    int            bits_per_pixel;
    int            line_length;
    int            endian;
}                t_data;

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int get_b(int trgb)
{
	return (trgb & 0xFF);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;
 
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;

	// char *dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	// *(unsigned int *)dst = color;
}

int main()
{
	void    *mlx;
    void    *mlx_win;
    t_data  img;
 
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 600, 400, "Hello world!");
    img.img = mlx_new_image(mlx, 600, 400);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    
    // my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	for (int i = 0; i < 200; i++)
		for (int j = 0; j < 100; j++)
			my_mlx_pixel_put(&img, j, i, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);

	// t_mlx mlx;
	// t_data img;

	// mlx.mlx = mlx_init();
	// mlx.win = mlx_new_window(mlx.mlx, 600, 400, "test");
	// img.img = mlx_new_image(mlx.mlx, 600, 400);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	// mlx_loop(mlx.mlx);
	return (0);
}