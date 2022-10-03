/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:29:39 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/03 18:09:10 by ddurrand         ###   ########.fr       */
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
			return (textures[2]);
		return (textures[3]);
	}
	if (sin(plr.dir) < 0)
		return (textures[0]);
	return (textures[1]);
}

int	get_img_y(t_cub3d *cub3d, double column_h, int y, int start_of_wall)
{
	double	img_y;

	img_y = round(cub3d->map_data.text_w_h[1] / column_h * (y - start_of_wall));
	if ((int)img_y < 0)
		img_y = 0;
	else if ((int)img_y >= cub3d->map_data.text_w_h[1])
		img_y = cub3d->map_data.text_w_h[1] - 1;
	return ((int)img_y);
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

void	draw_column(t_cub3d *cub3d, t_dda dda, int x)
{
	t_mlx	data_tex;
	double	column_h;
	int		y;
	int		img_x;
	int		start_of_wall;

	column_h = (int)(WIN_HEIGHT / dda.dist);
	if (column_h > WIN_HEIGHT)
	{
		y = 0;
		start_of_wall = (WIN_HEIGHT - column_h) / 2;
	}
	else
	{
		y = WIN_HEIGHT / 2 - (int)column_h / 2;
		start_of_wall = y;
	}
	set_img_x_and_data_tex(&img_x, cub3d, dda.x_y_rays, &data_tex);
	while (y < WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(&cub3d->mlx_data, x, y, get_img_color(data_tex, img_x, \
		get_img_y(cub3d, column_h, y, start_of_wall)));
		++y;
	}
	while (y < (WIN_HEIGHT / 2 + (int)column_h / 2) && y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&cub3d->mlx_data, x, y, get_img_color(data_tex, img_x, \
		get_img_y(cub3d, column_h, y, start_of_wall)));
		++y;
	}
}
