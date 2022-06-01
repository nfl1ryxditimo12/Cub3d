/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:47 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/01 19:35:08 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_map	t_map;
typedef enum e_bool	t_bool;
typedef enum e_dir	t_dir;

enum e_map
{
	FLOOR,
	WALL,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	CEILLING,
	SPRITE,
	DOOR,
	EMPTY_SPACE,
	NOTHING
};

enum
{
	VERT,
	HORIZ
};

enum e_bool
{
	false,
	true
};
enum e_dir
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_DOOR,
	DIR_SPRITE
};

#endif