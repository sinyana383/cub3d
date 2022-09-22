/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/22 20:14:43 by ddurrand         ###   ########.fr       */
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
				plr->start = plr->dir - FOV/2; // не уверена
				plr->end = plr->dir + FOV/2;
				return ;
			}
		}
	}
}

void	find_wall(t_plr plr, char **map)
{
	float	ray;
	int		x;
	int		y;

	ray = 0;
	x = (int)plr.x;
	y = (int)plr.y;
	while (ft_strchr("NWSE0", map[y][x]))
	{
		x = (int)(plr.x + ray * cosf(plr.dir)); // при возможности может округлиться в какую-то жопу
		y = (int)(plr.y - ray * sinf(plr.dir));
		ray += 0.1f;
	}
	printf("%d %d, %f\n", y, x, ray);
}

void	find_walls(t_plr plr, char **map)
{
	int		i;
	float	dir;

	i = -1;
	dir = plr.dir;
	//всего выпускается WIN_WIDTH лучей, на каждый пиксель
	while (++i < WIN_WIDTH)
	{
		// с каким шагом надо двигаться по углу, чтобы получилось на 640 пикселей?
		// делим 1.0472(60 град) на 640-1(отчет с нуля) частей и по этим частям ходим
		// от plr.start до plr.end
		plr.dir = plr.start + i * (FOV/(WIN_WIDTH-1));
		find_wall(plr, map);
	}
	plr.dir = dir;
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
