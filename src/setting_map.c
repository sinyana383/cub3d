/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:29:11 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/25 14:55:30 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				plr->x = (double)x + 0.001; // чтобы хоть как-то показать, что игрок стоит не на границе клетки
				plr->y = (double)y + 0.001;
				if (map[y][x] == 'N')
					plr->dir = M_PI / 2;
				else if (map[y][x] == 'W')
					plr->dir = M_PI;
				else if (map[y][x] == 'S')
					plr->dir = 3 * (M_PI / 2);
				else if (map[y][x] == 'E')
					plr->dir = 0;
				plr->start = plr->dir - FOV / 2;
				plr->end = plr->dir + FOV / 2;
				return ;
			}
		}
	}
}

int	set_map(t_cub3d	*cub3d, int argc, char **argv)
{
	cub3d->map_data.map = get_map(argc, argv);
	if (!cub3d->map_data.map)
		exit(0);
	set_plr(cub3d->map_data.map, &cub3d->plr);
	cub3d->mlx_data.mlx = mlx_init();
	cub3d->mlx_data.win = mlx_new_window(cub3d->mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub3d->mlx_data.img = mlx_new_image(cub3d->mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT);
	cub3d->mlx_data.addr = mlx_get_data_addr(cub3d->mlx_data.img, \
	&cub3d->mlx_data.bits_per_pixel, &cub3d->mlx_data.line_length, &cub3d->mlx_data.endian);
	draw_floor_and_celling(&cub3d->mlx_data, 0x00FBF6E6, 0x00A284AB);
	return (1);
}
