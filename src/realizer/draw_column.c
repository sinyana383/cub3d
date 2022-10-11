/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:29:39 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:32:48 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_img_color(t_mlx data, int x, int y)
{
	char	*color;

	color = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int *)color);
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

void	set_column_startofwall_and_y(double *column_h, \
									t_dda dda, int *y, int *start_of_wall)
{
	*column_h = (int)(WIN_HEIGHT / dda.dist);
	if (*column_h > WIN_HEIGHT)
	{
		*y = 0;
		*start_of_wall = (WIN_HEIGHT - *column_h) / 2;
	}
	else
	{
		*y = WIN_HEIGHT / 2 - (int)*column_h / 2;
		*start_of_wall = *y;
	}
}

void	draw_column(t_cub3d *cub3d, t_dda dda, int x)
{
	t_mlx	data_tex;
	double	column_h;
	int		y;
	int		img_x;
	int		start_of_wall;

	set_column_startofwall_and_y(&column_h, dda, &y, &start_of_wall);
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
