/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/22 17:15:06 by ddurrand         ###   ########.fr       */
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

void	set_plr(char **map, t_plr *plr)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr("NWES", map[y][x]))
			{
				plr->x = (float)x;
				plr->y = (float)y;
				if (map[y][x] == 'N')
					plr->dir = M_PI / 2;
				else if (map[y][x] == 'W')
					plr->dir = M_PI;
				else if (map[y][x] == 'S')
					plr->dir = 3 * (M_PI / 2);
				else if (map[y][x] == 'E')
					plr->dir = 0;
				return ;
			}
		}
	}
}

void	find_wall(t_plr plr, char **map)
{
	float	ray;
	float	x;
	float	y;

	ray = 0;
	x = plr.x;
	y = plr.y;
	while (map[(int)y][(int)x] == ' ' && \
	x < (float)WIN_WIDTH && y < (float)WIN_HEIGHT) // сравнение int и float
	{
		x = plr.x + ray * cosf(plr.dir); // cos(0) может колебаться
		y = plr.y - ray * sinf(plr.dir);
		ray += 0.5f;
	}
	printf("%d %d, %d\n", (int)y, (int)x, (int)ray); // как сделать норм кастинг?
}

int	main(int argc, char **argv)
{
	t_map	input_map;
	t_plr	plr;
	t_mlx	data;

	input_map.map = get_map(argc, argv);
	if (!input_map.map)
		exit(0);
	set_plr(input_map.map, &plr);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
								&data.line_length, &data.endian);
	draw_floor_and_celling(&data, 0x00F5F7F0, 0x00A284AB);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	find_wall(plr, input_map.map);
	mlx_loop(data.mlx);
}
