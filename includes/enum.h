/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:47 by seonkim           #+#    #+#             */
/*   Updated: 2022/05/31 18:03:54 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_map	t_map;

enum e_map
{
	CEILLING,
	WALL,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	SPRITE,
	DOOR,
	EMPTY_SPACE,
	NOTHING
};

enum { VERT, HORIZ };

typedef enum { false=0, true=1 } bool;
typedef enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;

#endif