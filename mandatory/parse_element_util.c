/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:21 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 22:00:09 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(void *mlx, t_texture *texture, char *filename)
{
	t_image	image;
	int		x;
	int		y;

	image.image = mlx_xpm_file_to_image(mlx, filename, &image.image_width, \
														&image.image_height);
	texture->texture_image = (int *)ft_alloc(sizeof(int) * \
								image.image_width * image.image_height);
	if (!image.image)
		return (0);
	image.addr = (int *)mlx_get_data_addr(image.image, &image.bit_per_pixel, \
											&image.size_line, &image.endian);
	y = -1;
	while (++y < image.image_height)
	{
		x = -1;
		while (++x < image.image_width)
			texture->texture_image[image.image_width * y + x] = \
							image.addr[image.image_width * y + x];
	}
	texture->texture_height = image.image_height;
	texture->texture_width = image.image_width;
	mlx_destroy_image(mlx, image.image);
	free(filename);
	return (1);
}

int	ft_atoi_max_unsigned_char(char *str, int *dest, int *flag)
{
	int	cnt;

	cnt = 0;
	*dest = 0;
	while (str[cnt] && (str[cnt] == 32 || str[cnt] == 9))
		cnt++;
	while (str[cnt] && str[cnt] != ',' && str[cnt] != 32 && str[cnt] != 9 \
			&& str[cnt] >= '0' && str[cnt] <= '9')
		*dest = *dest * 10 + str[cnt++] - '0';
	while (str[cnt] && (str[cnt] == 32 || str[cnt] == 9 || str[cnt] == ','))
		cnt++;
	if (str[cnt] && str[cnt] != ',' && str[cnt] != 32 && str[cnt] != 9 \
			&& !(str[cnt] >= '0' && str[cnt] <= '9'))
		*flag = 0;
	if (*dest > 255)
		*flag = 0;
	return (cnt);
}

int	load_color(int *dest, char *color_data)
{
	char	*ptr;
	int		flag;
	int		r;
	int		g;
	int		b;

	ptr = color_data;
	flag = 1;
	color_data += ft_atoi_max_unsigned_char(color_data, &r, &flag);
	color_data += ft_atoi_max_unsigned_char(color_data, &g, &flag);
	color_data += ft_atoi_max_unsigned_char(color_data, &b, &flag);
	*dest = encode_color(r, g, b);
	free(ptr);
	return (flag);
}
