/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:16:12 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/19 15:31:02 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>

typedef struct s_cub3d
{
	t_map	*map;
}	t_cub3d;

typedef struct s_map
{
	char			**map;			// карта
	char			*path[4];		// пути к текстуркам: [0,1,2,3] - north south east west
	unsigned int	celling_color;	// 0,1,2,3 байты - прозрач,red,green,blue
}	t_map;


#endif

/*
	Две части:
	- Парсер
		входные данные: map.cub
		выходные данные: структура t_map(смотри вверху)
	- Реализатор
		- draw
			- draw_floor_and_celling: ходим по адрессам всех пикселей и окрашиваем их
			- draw_walls
				- go along x and draw_lines
					1. determine angle by radians
					2. angle -> collision points
					3. collision points -> high of line
					4. print line by pixels
		- hook
*/