/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunpark <seunpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:16 by seonkim           #+#    #+#             */
/*   Updated: 2022/06/07 21:50:41 by seunpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_BONUS_H
# define DEFINE_BONUS_H

// Except map content, N,S,E and W file path & floor, ceilling color
# define ESSENTIAL_ELEMENTS	13
# define MAP_FILE_EXTENSION ".cub"

# define MAP_COL		15
# define MAP_ROW		11
# define PIXEL_SIZE		10
# define WALL_DEFAULT_HEIGHT	1000

# define PLAYER_COLOR	0xFF0000
# define WALL_COLOR		0x333333
# define FLOOR_COLOR	0x999999
# define GRID_COLOR		0xb3b3b3
# define RAY_COLOR		0xFFFF66
# define SPRITE_COLOR	0x33FF33
# define DOOR_COLOR		0xFF7F00

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_S			1
# define KEY_A			0
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_SPACEBAR	49

/* =========================== */

# define  EPS	1e-06

# define  SCREEN_WIDTH		1200
# define  SCREEN_HEIGHT		800
# define  FOV				60
# define  WALL_H			1.0

# define  _2PI		6.28318530717958647692

# define  ROT_UNIT	0.06
# define  MOVE_UNIT	0.15

# define BUFFER_SIZE	1000000

# define IDENTIFIER_NORTH			"NO"
# define IDENTIFIER_SOUTH			"SO"
# define IDENTIFIER_WEST			"WE"
# define IDENTIFIER_EAST			"EA"
# define IDENTIFIER_DOOR			"DO"
# define IDENTIFIER_FLOOR			"F"
# define IDENTIFIER_CEILLING		"C"
# define IDENTIFIER_SPRITE			"SP"
# define IDENTIFIER_SPRITE_ONE		"SP_1"
# define IDENTIFIER_SPRITE_TWO		"SP_2"
# define IDENTIFIER_SPRITE_THREE	"SP_3"
# define IDENTIFIER_SPRITE_FOUR		"SP_4"
# define IDENTIFIER_SPRITE_FIVE		"SP_5"
# define IDENTIFIER_SPRITE_SIX		"SP_6"

# define ERROR_LEVEL	"Error"
# define INFO_LEVEL		"Info"

# define MEMORY_FAIL		"memory allocate fail"
# define INVALID_FILENAME	"Usage: \"./cub3D ./map/example.cub\""
# define INVALID_FILEDATA	"is a broken file"
# define INVALID_DOOR		"door location is invalid"
# define INVALID_ELEMENT	"around element is invalid"
# define INVALID_PLAYER		"invalid player count"
# define INVALID_MAP		"invalid map"
# define DOUBLE_MAP			"map must be connected"
# define NOT_ENOUGH_ELEMENT	"essential elements is not enough"

#endif
