/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_img_x_and_data_tex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:25:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:25:41 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*get_texture(t_plr plr, double x_y_rays[2], void *textures[4])
{
	if (x_y_rays[0] - x_y_rays[1] < 0)
	{
		if (cos(plr.dir) < 0)
			return (textures[2]);
		return (textures[3]);
	}
	if (sin(plr.dir) < 0)
		return (textures[0]);
	return (textures[1]);
}

void	set_img_x_and_data_tex(int *img_x, t_cub3d *cub3d, \
								double x_y_rays[2], t_mlx *data_tex)
{
	double	point;
	double	k;

	data_tex->img = get_texture(cub3d->plr, x_y_rays, cub3d->map_data.textures);
	data_tex->mlx = cub3d->mlx_data.mlx;
	data_tex->addr = mlx_get_data_addr(data_tex->img, \
	&data_tex->bits_per_pixel, &data_tex->line_length, &data_tex->endian);
	if (x_y_rays[0] - x_y_rays[1] < 0)
		point = cub3d->plr.y - x_y_rays[0] * sin(cub3d->plr.dir);
	else
		point = cub3d->plr.x + x_y_rays[1] * cos(cub3d->plr.dir);
	k = point - (int)point;
	*img_x = round(k * cub3d->map_data.text_w_h[0]);
	if (*img_x < 0)
		*img_x = 0;
	else if (*img_x >= cub3d->map_data.text_w_h[0])
		*img_x = cub3d->map_data.text_w_h[0] - 1;
}
