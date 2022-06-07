/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_view_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:52:25 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 17:04:05 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
