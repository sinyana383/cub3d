/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:47:40 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:58:21 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_and_celling(t_mlx *data, int color_celling, int color_floor)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(data, x, y, color_celling);
		++y;
	}
	while (y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(data, x, y, color_floor);
		++y;
	}
}
