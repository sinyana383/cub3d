/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:16:12 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/03 17:52:20 by ddurrand         ###   ########.fr       */
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

typedef struct s_dda
{
	int		x_y_cur[2];
	int		x_y_steps[2];
	double	x_y_rays[2];
	double	dist;
}	t_dda;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;			// массив 
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_plr
{
	double	x;
	double	y;
	double	dir;
	double	start;	// ? на каком месте поле зрения начинается
	double	end;	// ? на каком месте поле зрения заканчивается на карте
}	t_plr;

typedef struct s_map
{
	char	**map;			// карта, из char в int можно просто (int)var
	void	*textures[4];		// пути к текстуркам: [0,1,2,3] - north south east west
	int		text_w_h[2];
	int		celling_color;	// 0,1,2,3 байты - прозрач,red,green,blue
	int		floor_color;
}	t_map;

typedef struct s_cub3d
{
	t_mlx	mlx_data;
	t_map	map_data;
	t_plr	plr;
}	t_cub3d;

// DESINES
# define WIN_WIDTH	640
# define WIN_HEIGHT	480

# define FOV 		1.0471975512 // угол обзора 60-ти градусов в радианах
# define ROT_STEP	0.0924291465 // угол поворота 10-ти градусов
# define MOVE_STEP	0.2

# define LEFT_KEY	123
# define RIGHT_KEY	124
# define W_KEY		13
# define A_KEY		0
# define S_KEY		1
# define D_KEY		2
# define ESC_KEY	53

int		set_map(t_cub3d	*cub3d, int argc, char **argv);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	draw_floor_and_celling(t_mlx *data, int color_celling, int color_floor);
void	find_dist_and_draw_column(t_cub3d *cub3d, int x, double main_dir);
void	draw_column(t_cub3d *cub3d, t_dda dda, int x);

// DELETE
void 	DEBUG();

#endif

/*
	Две части и бонус:
	
	- Парсер
		входные данные: map.cub
		выходные данные: структура t_map(смотри вверху)
	- Реализатор
		- draw
			+ draw_floor_and_celling: ходим по адрессам всех пикселей и окрашиваем их
			+ draw_walls
			+ different colors for sides of walls
			- прорисовка текстур
	- Hooks
		+ крутиться по стрелкам
		+ передвигаться по WASD
		- закрытие на крестик
		
	- Bonus
		+ крутиться мышкой
		- миникарта - это отрисовка so_long-a
		только в маленьком размере в одном из углу
		- не проходит через стены
			- между двумя кубиками в углу нельзя протиснуться
			- через уголки стен нельзя проходить
			- скольжение по стенке
	- СЕГИ
		- следи, чтобы в my_pixel_put были норм x и y
	- БАГИ
		- странные линии внизу на стенках ()

		111111111111111
		100000101010001
		100000111011001
		100000001101001
		100000000000111
		100000000011011
		1000N0000001111
		100000000001111
		111111111111111
*/