/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:16:12 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/22 16:45:04 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "math.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_plr
{
	float	x;
	float	y;
	float	dir;
	float	start;	// ? на каком месте поле зрения начинается
	float	end;	// ? на каком месте поле зрения заканчивается на карте
}	t_plr;

typedef struct s_map
{
	char			**map;			// карта, из char в int можно просто (int)var
	char			*path[4];		// пути к текстуркам: [0,1,2,3] - north south east west
	unsigned int	celling_color;	// 0,1,2,3 байты - прозрач,red,green,blue
	unsigned int	floor_color;
}	t_map;

typedef struct s_cub3d
{
	t_mlx	*mlx;
	t_map	*map;
	t_plr	*plr;
}	t_cub3d;

// DESINES
# define WIN_WIDTH	640
# define WIN_HEIGHT	480
# define FOV 		1.0472	// угол обзора 60-ти градусов в радианах

#endif

/*
	Две части:
	- Парсер
		входные данные: map.cub
		выходные данные: структура t_map(смотри вверху)
	- Реализатор
		- draw
			+ draw_floor_and_celling: ходим по адрессам всех пикселей и окрашиваем их
			- find wall
			- draw_walls
				- go along x and draw_lines
					1. determine angle by radians
					2. angle -> collision points
					3. collision points -> high of line
					4. print line by pixels
				- или реализовать перпендикулярным ветором к направлению
		- hook
	- Bonus
		- миникарта - это отрисовка so_long-a
		только в маленьком размере в одном из углу
*/