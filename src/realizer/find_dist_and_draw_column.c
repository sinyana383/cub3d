/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dist_and_draw_column.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:59:10 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:23:25 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		x_y_rays[0] += sqrt(1.0 + tan(plr.dir) * tan(plr.dir));
	else
		x_y_rays[1] += sqrt(1.0 + 1.0 / tan(plr.dir) * 1.0 / tan(plr.dir));
	if (x_y_rays[0] - x_y_rays[1] < 0)
		x_y_cur[0] += x_y_steps[0];
	else
		x_y_cur[1] += x_y_steps[1];
}

void	find_dist_and_draw_column(t_cub3d *cub3d, int x, double main_dir)
{
	t_dda	dda;

	set_start_rays_and_steps(cub3d->plr, &dda.x_y_rays[0], \
	&dda.x_y_rays[1], dda.x_y_steps);
	dda.x_y_cur[0] = floor(cub3d->plr.x);
	dda.x_y_cur[1] = floor(cub3d->plr.y);
	if (dda.x_y_rays[0] - dda.x_y_rays[1] < 0)
		dda.x_y_cur[0] += dda.x_y_steps[0];
	else
		dda.x_y_cur[1] += dda.x_y_steps[1];
	while (ft_strchr("NWSE0", \
	cub3d->map_data.map[dda.x_y_cur[1]][dda.x_y_cur[0]]))
		set_rays(cub3d->plr, dda.x_y_rays, dda.x_y_cur, dda.x_y_steps);
	if (dda.x_y_rays[0] - dda.x_y_rays[1] < 0)
		dda.dist = dda.x_y_rays[0] * cos(cub3d->plr.dir - main_dir);
	else
		dda.dist = dda.x_y_rays[1] * cos(cub3d->plr.dir - main_dir);
	draw_column(cub3d, dda, x);
}
