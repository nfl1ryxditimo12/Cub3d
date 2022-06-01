/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:55:25 by seunpark          #+#    #+#             */
/*   Updated: 2022/06/01 17:57:42 by seonkim          ###   ########.fr       */
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

int	parse_cub3d_data(t_var *var, char *filename);
int	check_valid_map(t_var *var);

int	encode_color(int r, int g, int b);

#endif