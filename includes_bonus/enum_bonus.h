/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:47 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:33:44 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_BONUS_H
# define ENUM_BONUS_H

typedef enum e_map	t_map;
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
	CLOSE_DOOR,
	EMPTY_SPACE,
	NOTHING,
	OPEN_DOOR,
};

enum
{
	VERT,
	HORIZ
};

enum e_dir
{
	DIR_NORTH,
	DIR_SOUTH,
	DIR_WEST,
	DIR_EAST,
	DIR_DOOR,
	DIR_SPRITE_ONE,
	DIR_SPRITE_TWO,
	DIR_SPRITE_THREE,
	DIR_SPRITE_FOUR,
	DIR_SPRITE_FIVE,
	DIR_SPRITE_SIX
};

#endif
