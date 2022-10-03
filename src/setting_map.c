/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:29:11 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/03 18:26:42 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	set_map_data(t_cub3d *cub3d)
{
	t_map	*map_data;
	t_mlx	*mlx;

	map_data = &cub3d->map_data;
	mlx = cub3d->mlx_data.mlx;
	map_data->textures[0] = mlx_xpm_file_to_image \
	(mlx, "textures/north.xpm", &map_data->text_w_h[0], &map_data->text_w_h[1]);
	map_data->textures[1] = mlx_xpm_file_to_image \
	(mlx, "textures/south.xpm", &map_data->text_w_h[0], &map_data->text_w_h[1]);
	map_data->textures[2] = mlx_xpm_file_to_image \
	(mlx, "textures/east.xpm", &map_data->text_w_h[0], &map_data->text_w_h[1]);
	map_data->textures[3] = mlx_xpm_file_to_image \
	(mlx, "textures/west.xpm", &map_data->text_w_h[0], &map_data->text_w_h[1]);
	if (map_data->textures[0] && map_data->textures[1] && \
	map_data->textures[2] && map_data->textures[3])
		return ;
	printf("texture opening error\n");
	exit (EXIT_FAILURE);
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
				plr->x = (double)x + 0.5; // чтобы хоть как-то показать, что игрок стоит не на границе клетки
				plr->y = (double)y + 0.5;
				if (map[y][x] == 'N')
					plr->dir = M_PI / 2;
				else if (map[y][x] == 'W')
					plr->dir = M_PI;
				else if (map[y][x] == 'S')
					plr->dir = 3 * (M_PI / 2);
				else if (map[y][x] == 'E')
					plr->dir = 0;
				plr->start = plr->dir + FOV / 2;
				plr->end = plr->dir - FOV / 2;
				return ;
			}
		}
	}
}

int	set_map(t_cub3d	*cub3d, int argc, char **argv)
{
	cub3d->map_data.map = get_map(argc, argv);
	if (!cub3d->map_data.map)
		exit(EXIT_FAILURE);
	set_plr(cub3d->map_data.map, &cub3d->plr);
	cub3d->mlx_data.mlx = mlx_init();
	set_map_data(cub3d);
	cub3d->mlx_data.win = mlx_new_window(cub3d->mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub3d->mlx_data.img = mlx_new_image(cub3d->mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT);
	cub3d->mlx_data.addr = mlx_get_data_addr(cub3d->mlx_data.img, \
	&cub3d->mlx_data.bits_per_pixel, &cub3d->mlx_data.line_length, &cub3d->mlx_data.endian);
	draw_floor_and_celling(&cub3d->mlx_data, 0x00C8E8FC, 0x00293640);
	return (1);
}
