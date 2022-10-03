/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:29:39 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/03 17:16:37 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_img_color(t_mlx data, int x, int y)
{
	char	*color;

	color = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int *)color);
}

void	*get_texture(t_plr plr, double x_y_rays[2], void *textures[4])
{
	if (x_y_rays[0] - x_y_rays[1] < 0)
	{
		if (cos(plr.dir) < 0)
			return (textures[2]);	//e
		return (textures[3]);		//w
	}
	if (sin(plr.dir) < 0)
		return (textures[0]); 		//n
	return (textures[1]);			//s
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
}

void	draw_column(t_cub3d *cub3d, t_dda dda, int x)
{
	t_mlx	data_tex;
	double	column_h;
	int		y;
	int		img_x;

	set_img_x_and_data_tex(&img_x, cub3d, dda.x_y_rays, &data_tex);
	if (dda.dist - 0.1 < 0)
		column_h = WIN_HEIGHT;
	else
		column_h = (int)(WIN_HEIGHT / dda.dist);
	if (column_h > WIN_HEIGHT)
		column_h = WIN_HEIGHT;
	y = WIN_HEIGHT / 2 - (int)column_h / 2;
	while (y < WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(&cub3d->mlx_data, x, y, get_img_color(data_tex, \
		img_x, round(cub3d->map_data.text_w_h[1] / column_h * y)));
		++y;
	}
	while (y < (WIN_HEIGHT / 2 + (int)column_h / 2))
	{
		my_mlx_pixel_put(&cub3d->mlx_data, x, y, get_img_color(data_tex, \
		img_x, round(cub3d->map_data.text_w_h[1] / column_h * y)));
		++y;
	}
}
