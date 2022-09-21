/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/21 18:24:50 by ddurrand         ###   ########.fr       */
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

char	**get_map(int argc, char **argv)
{
	int		fd;
	char	**map;

	if (argc < 2)
		return (0);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(".cub") + 1))
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	map = get_map_from_file(fd, argv[1]);
	return (map);
}

void	find_wall(t_plr plr, char **map)
{
	float	ray;
	float	x;
	float	y;
	//сначала просто запусти луч, паралелльный x или y, \
	потом смотри по https://proglib.io/p/raycasting-for-the-smallest
	ray = 0;
	while (x < WIN_WIDTH && y < WIN_HEIGHT) //???
	{
		x = plr.x + ray * cosf(plr.dir);
		y = plr.y + ray * sinf(plr.dir);
		ray += 0.5f;
	}
}

int	main(int argc, char **argv)
{
	t_map	input_map;
	t_mlx	data;

	input_map.map = get_map(argc, argv);
	if (!input_map.map)
		exit(0);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
								&data.line_length, &data.endian);
	draw_floor_and_celling(&data, 0x00F5F7F0, 0x00A284AB);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
