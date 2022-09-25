/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/25 14:56:09 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	my_cos_sin(double angle, char s_c)
{
	if (s_c == 's')
		return (roundl(sinl(angle) * 100000) / 100000);
	return (roundl(cosl(angle) * 100000) / 100000);
}

void	draw_column(t_mlx *data, double ray, int x)
{
	double	column_height;
	int		y;

	column_height = roundl(1.0 / ray * 1000) / 1000;
	if (column_height - 1000.0 >= 0)
		column_height = WIN_HEIGHT;
	else
		column_height = (int)(WIN_HEIGHT * column_height / 1000.0);
	y = WIN_HEIGHT / 2 - roundl(column_height / 2);
	while (y < WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(data, x, y, 0x008C74AC);
		++y;
	}
	while (y < WIN_HEIGHT / 2 + (column_height / 2))
	{
		my_mlx_pixel_put(data, x, y, 0x008C74AC);
		++y;
	}
}

double	ray_len(double ray, t_plr plr)
{
	double		del_x;	// меняется: то со знаком, то без
	double		del_y;

	del_x = ray * my_cos_sin(plr.dir, 'c');
	del_y = ray * my_cos_sin(plr.dir, 's') * (-1);
	if (del_x > 0)
	{
		del_x = plr.x + del_x;	// перемещение по x на правильную линию
		del_x = floorl(del_x);
		if ((int)del_x - (int)floorl(plr.x) <= 0) // если del_x даже на одну линию не переместился от игрока
			del_x = INFINITY;
	}
	else
	{
		del_x = plr.x + del_x;
		del_x = ceill(del_x);
		if ((int)del_x - (int)ceill(plr.x) >= 0)
			del_x = INFINITY;
	}
	if (del_y > 0)
	{
		del_y = plr.y + del_y;
		del_y = floorl(del_y);
		if ((int)del_y - (int)floorl(plr.y) <= 0)
			del_y = INFINITY;
	}
	else
	{
		del_y = plr.y + del_y;
		del_y = ceill(del_y);
		if ((int)del_y - (int)ceill(plr.y) >= 0)
			del_y = INFINITY;
	}
	if (del_x == INFINITY && del_y == INFINITY) // притык к стенке, например: "1E" смотрит на восток и к стене прижался
		printf ("error: ray_len");
	if (del_x == INFINITY)
		return (fabs(del_y - plr.y));
	if (del_y == INFINITY)
		return (fabs(del_x - plr.x));
	del_x = fabs(del_x - plr.x);
	del_y = fabs(del_y - plr.y);
	if (del_x - del_y > 0)
		return (del_x);
	return (del_y);
}

void	find_wall(t_plr plr, char **map, int i, t_mlx *data)
{
	double	ray;
	int		x;
	int		y;

	ray = 0;
	x = (int)plr.x;
	y = (int)plr.y;
	while (ft_strchr("NWSE0", map[(int)y][(int)x]))
	{
		ray += 0.001;		// лучше сделать с шагом по линиям, тип: x > 0 ceill(x),
		x = floorl(plr.x + ray * my_cos_sin(plr.dir, 'c'));
		y = floorl(plr.y - ray * my_cos_sin(plr.dir, 's'));
	}
	// определить какую ось по x и по y пересекли
	ray = ray_len(ray, plr);
	draw_column(data, ray, i);
	// printf("angle:%f\nx - %d y - %d, ray - %lf\n", \
	// plr.dir * (180.0 / M_PI), x, y, );
}

void	find_walls(t_cub3d *cub3d, char **map)
{
	int		i;
	double	dir;
	double	rad_step;

	dir = cub3d->plr.dir;
	rad_step = FOV / (WIN_WIDTH - 1);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub3d->plr.dir = cub3d->plr.start + i * rad_step;
		find_wall(cub3d->plr, map, i, &cub3d->mlx_data);
	}
	cub3d->plr.dir = dir;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	set_map(&cub3d, argc, argv);
	find_walls(&cub3d, cub3d.map_data.map);
	mlx_put_image_to_window(cub3d.mlx_data.mlx, \
	cub3d.mlx_data.win, cub3d.mlx_data.img, 0, 0);
	mlx_loop(cub3d.mlx_data.mlx);
}
