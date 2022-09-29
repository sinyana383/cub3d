/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dist_and_draw_column.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:59:10 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/29 18:00:06 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_column(t_mlx *data, double dist, int x, int color)
{
	double	half_column;
	int		y;

	half_column = (int)(WIN_HEIGHT / dist / 2);
	if (half_column > WIN_HEIGHT / 2)
		half_column = WIN_HEIGHT / 2;
	y = WIN_HEIGHT / 2 - (int)half_column;
	while (y < WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(data, x, y, color);
		++y;
	}
	while (y < (WIN_HEIGHT / 2 + (int)half_column))
	{
		my_mlx_pixel_put(data, x, y, color);
		++y;
	}
}

void	set_start_rays_and_steps(t_plr plr, double *ray_x, double *ray_y, \
						int x_y_steps[2])
{
	double	del;

	if (cos(plr.dir) < 0)
	{
		x_y_steps[0] = -1;
		del = (plr.x) - floor(plr.x);
	}
	else
	{
		x_y_steps[0] = 1;
		del = ceil(plr.x) - plr.x;
	}
	*ray_x = sqrt(del * del + (tan(plr.dir) * del) * (tan(plr.dir) * del));
	if (sin(plr.dir) > 0)
	{
		x_y_steps[1] = -1;
		del = (plr.y) - floor(plr.y);
	}
	else
	{
		x_y_steps[1] = 1;
		del = ceil(plr.y) - plr.y;
	}
	*ray_y = sqrt(del * del + (del / tan(plr.dir)) * (del / tan(plr.dir)));
}

void	set_rays(t_plr plr, double x_y_rays[2], int x_y_cur[2], \
				int x_y_steps[2])
{
	if (x_y_rays[0] - x_y_rays[1] < 0)
		x_y_rays[0] += sqrt(1.0 + tan(plr.dir) * tan(plr.dir)); // 1.0 == x_y_steps[0,1] * x_y_steps[0,1]
	else
		x_y_rays[1] += sqrt(1.0 + 1.0 / tan(plr.dir) * 1.0 / tan(plr.dir));
	if (x_y_rays[0] - x_y_rays[1] < 0)
		x_y_cur[0] += x_y_steps[0];
	else
		x_y_cur[1] += x_y_steps[1];
}

int	get_color(t_plr plr, double x_y_rays[2])
{
	if (x_y_rays[0] - x_y_rays[1] < 0)
	{
		if (cos(plr.dir) < 0)
			return (0x00A257B9);	//e
		return (0x00EABEF7);		//w
	}
	if (sin(plr.dir) < 0)
		return (0x004C2957); 		//n
	return (0x00715C78);			//s
}

void	find_dist_and_draw_column(t_cub3d *cub3d, int x, double main_dir)
{
	int		x_y_cur[2];
	int		x_y_steps[2];
	double	x_y_rays[2];
	double	ray;

	set_start_rays_and_steps(cub3d->plr, &x_y_rays[0], &x_y_rays[1], x_y_steps);
	x_y_cur[0] = floor(cub3d->plr.x);
	x_y_cur[1] = floor(cub3d->plr.y);
	if (x_y_rays[0] - x_y_rays[1] < 0)
		x_y_cur[0] += x_y_steps[0];
	else
		x_y_cur[1] += x_y_steps[1];
	while (ft_strchr("NWSE0", cub3d->map_data.map[x_y_cur[1]][x_y_cur[0]]))
		set_rays(cub3d->plr, x_y_rays, x_y_cur, x_y_steps);
	if (x_y_rays[0] - x_y_rays[1] < 0)
		ray = x_y_rays[0];
	else
		ray = x_y_rays[1];
	draw_column(&cub3d->mlx_data, ray * cos(cub3d->plr.dir - main_dir), \
	x, get_color(cub3d->plr, x_y_rays));
}
