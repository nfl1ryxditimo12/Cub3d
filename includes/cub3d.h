/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:55:25 by seunpark          #+#    #+#             */
/*   Updated: 2022/06/07 19:36:54 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <time.h>

# include "define.h"
# include "enum.h"
# include "struct.h"

/**
 * @brief 기본 규칙
 *
 * return 값 0 인 경우 - 성공
 * return 값 1 인 경우 - 실패
 * return 값 2 인 경우 - 실패 (texture 구조체 메모리 해제 필요)
 * return 값 3 인 경우 - 실패 (texture 구조체, map 배열 메모리 해제 필요)
 *
 * 모든 변수는 직관적으로 설정
 *
 * 텍스쳐 데이터 6개 파싱 -> 맵 데이터 파싱 -> 맵 데이터 유효성 검사 -> 맵 데이터 구조체 할당
 */

int		parse_cub3d_data(t_var *var, char *filename);
int		check_valid_map(t_var *var);

int		encode_color(int r, int g, int b);

int		parse_error(int errno, char *level, char *err);
int		close_window(t_var *var);

void	handling_door(t_var *var, t_wall *wall);

/* ============================================= */
/*                 Ray Casting                   */
/* ============================================= */

/* ray_casting.c */
void	get_wall_intersection(t_var *var, double ray,
			t_wall *wall, t_sprite *sprite);
void	cast_single_ray(t_var *var, int x, t_wall *wall, t_sprite *sprite);
void	ray_casting(t_var *var, t_wall *wall, t_sprite *sprite);
int		put_element_coordinate(t_intersection *inter, t_wall *wall, \
											t_sprite *sprite);

/* ray_casting_init.c */
void	init_intersection(t_var *var, t_intersection *inter, double ray);
void	init_ray_casting(t_wall *wall, t_sprite *sprite);

/* ray_casting_math_util.c */
double	get_dist(double x0, double y0, double x1, double y1);
double	get_fov_min_dist(void);
double	degree_to_radian(double degree);
double	radian_to_degree(double radian);
double	angle_per_pixel(void);

/* ray_casting_view_util.c */
double	fov_h_2(void);
double	fov_h(void);
double	fov_v(void);

/* ray_casting_render_util.c */
int		is_zero(double d);
int		determin_angle(double d);
int		map_get_cell(t_game *game, int x, int y);
int		get_wall_height(double dist);

/* ray_casting_intersection_util.c */
void	get_slope(t_intersection *inter, double ray);
void	get_map_coordinate(t_intersection *inter);
void	get_next_distance(t_intersection *inter);
void	put_vertical_element_coord(t_intersection *inter, t_wall *wall, \
											t_sprite *sprite);
void	put_horizontal_element_coord(t_intersection *inter, t_wall *wall, \
											t_sprite *sprite);

/* ============================================= */
/*                     Draw                      */
/* ============================================= */

/* draw.c */
void	draw_game(t_var *var);

/* draw_map_util.c */
void	draw_line(t_image *image, t_offset p1, t_offset p2, int color);
void	draw_rectangle(t_var *var, int x, int y, int color);
void	draw_rectangles(t_var *var);

/* draw_render_util.c */
void	draw_sprite(t_var *var, t_sprite *sprite, int x);
void	draw_wall(t_var *var, t_wall *wall, int x);

/* ============================================= */
/*                     Init                      */
/* ============================================= */

/* init.c */
int		cub3d_init(t_var *var, char *filename);
int		main_loop(t_var *var);
void	image_init(t_var *var);
void	mlx_image_put(t_var *var);

/* ============================================= */
/*                      Key                      */
/* ============================================= */

/* key.c */
int		player_move(t_game *game, int key);
void	player_rotate(t_game *pp, double th);
int		deal_key(int key_code, t_var *var);

/* ============================================= */
/*                     Parse                     */
/* ============================================= */

/* parse_file_util.c */
int		check_file_extension(char *filename, char *extension);
char	*read_file(char *filename);
char	*get_filename(char *buffer);

/* parse_map_util.c */
int		is_empty_line(char *buffer);
int		get_map_size(char *buffer);
void	insert_map_data(t_map *line, char data);

/* parse_element_util.c */
int		load_texture(void *mlx, t_texture *texture, char *filename);
int		ft_atoi_max_unsigned_char(char *str, int *dest, int *flag);
int		load_color(int *dest, char *color_data);
int		get_sprite(t_var *var, char *buffer);

/* parse_util.c */
int		check_newline(char **arr);
int		until_next_space(char *str);
int		get_line_size(char *str);

/* ============================================= */
/*                     Check                     */
/* ============================================= */

/* check_resize_util.c */
int		get_map_line_size(t_map *line);
t_map	*resize_line(t_map *line, int max_size, int line_size);

/* check_wall_util.c */
int		check_double_map(t_var *var);
void	substitution_wall(t_var *var, int row, int col);
void	restore_wall(t_var *var, int row, int col);

/* check_element_util.c */
int		check_around_elements(t_var *var, int row, int col, int flag);
int		is_player_element(t_map elem);
int		set_player_pos(t_var *var, int row, int col);
int		check_valid_door(t_map **map, int row, int col);

/* ============================================= */
/*                     Util                      */
/* ============================================= */

/* memory_util.c */
void	*ft_alloc(int size);
void	**ft_dalloc(int size);
void	free_memory(t_var *var, int errno);

/* libft_util.c */
int		ft_str_len(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_max(int a, int b);
char	*ft_strdup(char *str);

/* color_util.c */
int		encode_color(int r, int g, int b);
int		fade_color(int color, double lum);
void	decode_color(int color, int *r, int *g, int *b);
double	get_luminosity(t_var *var, double dist);

#endif
