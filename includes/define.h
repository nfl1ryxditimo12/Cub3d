/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonkim <seonkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:16 by seonkim           #+#    #+#             */
/*   Updated: 2022/05/31 19:58:56 by seonkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// Except map content, N,S,E and W file path & floor, ceilling color
# define ESSENTIAL_ELEMENTS 6
# define MAP_FILE_EXTENSION ".cub"

# define MAP_COL		15 // 아마 미니맵 기본값으로 바뀔 예정
# define MAP_ROW		11
# define PIXEL_SIZE	32
# define WALL_DEFAULT_HEIGHT	1000

# define PLAYER_COLOR	0xFF0000
# define WALL_COLOR		0x333333
# define SPACE_COLOR	0x999999
# define GRID_COLOR		0xb3b3b3
# define DIR_COLOR		0xFFFF66

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_S			1
# define KEY_A			0
# define KEY_D			2
# define KEY_LEFT		123
# define KEY_RIGHT		124

/* =========================== */

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

#define  SCREEN_WIDTH         1200     /* screen width */
#define  SCREEN_HEIGHT         800     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SCREEN_HEIGHT/(double)SCREEN_WIDTH)
#define  WALL_H     1.0


#define  MAPX   14
#define  MAPY   33

# define  _2PI       6.28318530717958647692  /* 2 * M_PI */

# define  ROT_UNIT   0.06    /* rad */
# define  MOVE_UNIT  0.15

# define BUFFER_SIZE	10000000

# define IDENTIFIER_NORTH		"NO"
# define IDENTIFIER_SOUTH		"SO"
# define IDENTIFIER_WEST		"WEST"
# define IDENTIFIER_EAST		"EA"
# define IDENTIFIER_FLOOR		"F"
# define IDENTIFIER_CEILLING	"C"

#endif