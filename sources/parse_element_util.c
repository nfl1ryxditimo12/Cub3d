/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:21 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/06 19:11:27 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(void *mlx, t_texture *texture, char *filename)
{
	t_image	image;
	int		x;
	int		y;

	// 잘못된 image 경로 들어왔을 때 터지는거 확인해야함
	image.image = mlx_xpm_file_to_image(mlx, filename, &image.image_width, \
														&image.image_height);
	texture->texture_image = (int *)ft_alloc(sizeof(int) * \
								image.image_width * image.image_height);
	if (!image.image || !texture->texture_image)
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
	if (filename)
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
	while (str[cnt] && str[cnt] != ',' && str[cnt] != 32 && str[cnt] != 9 &&
			str[cnt] >= '0' && str[cnt] <= '9')
		*dest = *dest * 10 + str[cnt++]	- '0';
	while (str[cnt] && (str[cnt] == 32 || str[cnt] == 9 || str[cnt] == ','))
		cnt++;
	if (str[cnt] && str[cnt] != ',' && str[cnt] != 32 && str[cnt] != 9 &&
		!(str[cnt] >= '0' && str[cnt] <= '9'))
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

int	get_sprite(t_var *var, char *buffer)
{
	int flag;

	flag = 0;
	if (!ft_strcmp(buffer, IDENTIFIER_SPRITE_ONE))
		flag = load_texture(var->mlx, &var->texture[5], get_filename(buffer));
	else if (!ft_strcmp(buffer, IDENTIFIER_SPRITE_TWO))
		flag = load_texture(var->mlx, &var->texture[6], get_filename(buffer));
	else if (!ft_strcmp(buffer, IDENTIFIER_SPRITE_THREE))
		flag = load_texture(var->mlx, &var->texture[7], get_filename(buffer));
	else if (!ft_strcmp(buffer, IDENTIFIER_SPRITE_FOUR))
		flag = load_texture(var->mlx, &var->texture[8], get_filename(buffer));
	else if (!ft_strcmp(buffer, IDENTIFIER_SPRITE_FIVE))
		flag = load_texture(var->mlx, &var->texture[9], get_filename(buffer));
	else if (!ft_strcmp(buffer, IDENTIFIER_SPRITE_SIX))
		flag = load_texture(var->mlx, &var->texture[10], get_filename(buffer));
	return (flag);
}