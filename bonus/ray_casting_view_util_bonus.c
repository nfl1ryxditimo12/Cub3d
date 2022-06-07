/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_view_util_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:52:25 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:41:01 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	fov_h_2(void)
{
	return (degree_to_radian(FOV) / 2.0);
}

double	fov_h(void)
{
	return (degree_to_radian(FOV));
}

double	fov_v(void)
{
	double	fh;

	fh = fov_h();
	return (fh * (double)SCREEN_HEIGHT / (double)SCREEN_WIDTH);
}
