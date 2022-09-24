/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/24 13:56:40 by ddurrand         ###   ########.fr       */
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
				plr->x = (double)x;
				plr->y = (double)y;
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

double	ray_len(double ray, t_plr plr)
{
	double		del_x;	// меняется: то со знаком, то без
	double		del_y;
	int			plus_minus;

	plus_minus = 1;
	if (cosl(plr.dir) < 0)
		plus_minus = -1;
	del_x = ray * cosl(ray) * plus_minus;
	plus_minus = 1;
	if (sinl(plr.dir) > 0)
		plus_minus = -1;
	del_y = ray * sinl(ray) * plus_minus;
	if (del_x > 0)
	{
		del_x = plr.x + del_x;	// перемещение по x на правильную линию
		del_x = floorl(del_x);
		if ((int)del_x - (int)plr.x <= 0) // если del_x даже на одну линию не переместился от игрока
			del_x = INFINITY;
	}
	else
	{
		del_x = plr.x + del_x;
		del_x = ceill(del_x);
		if ((int)del_x - (int)plr.x >= 0)
			del_x = INFINITY;
	}
	if (del_y > 0)
	{
		del_y = plr.y + del_y;
		del_y = floorl(del_y);
		if ((int)del_y - (int)plr.y <= 0)
			del_y = INFINITY;
	}
	else
	{
		del_y = plr.y + del_y;
		del_y = ceill(del_y);
		if ((int)del_y - (int)plr.y >= 0)
			del_y = INFINITY;
	}
	if (del_x == INFINITY && del_y == INFINITY)
		printf ("error: ray_len");
	if (del_x == INFINITY)
		return (fabs(del_y - plr.y));
	if (del_y == INFINITY)
		return (fabs(del_x - plr.x));
	del_x = fabs(del_x - plr.x);
	del_y = fabs(del_y - plr.y);
	if (del_x - del_y > 0)
		return (del_x);
	return (del_y);
}

void	find_wall(t_plr plr, char **map)
{
	double	ray;
	int		x;
	int		y;

	ray = 0;
	x = (int)plr.x;
	y = (int)plr.y;
	while (ft_strchr("NWSE0", map[(int)y][(int)x]))
	{
		ray += 0.001f; // 0.001f;
		x = floorl(plr.x + ray * cosl(plr.dir)); // установить границу для округления
		y = floorl(plr.y - ray * sinl(plr.dir));
	}
	// определить какую ось по x и по y пересекли
	printf("angle:%f\nx - %d y - %d, ray - %lf\n", \
	plr.dir * (180.0 / M_PI), x, y, ray_len(ray, plr));
}

void	find_walls(t_plr plr, char **map)
{
	int		i;
	double	dir;
	double	rad_step;

	dir = plr.dir;
	rad_step = FOV / (WIN_WIDTH - 1);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		plr.dir = plr.start + i * rad_step;
		find_wall(plr, map);
	}
	plr.dir = dir;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	cub3d.map_data.map = get_map(argc, argv);
	if (!cub3d.map_data.map)
		exit(0);
	set_plr(cub3d.map_data.map, &cub3d.plr);
	cub3d.mlx_data.mlx = mlx_init();
	cub3d.mlx_data.win = mlx_new_window(cub3d.mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub3d.mlx_data.img = mlx_new_image(cub3d.mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT);
	cub3d.mlx_data.addr = mlx_get_data_addr(cub3d.mlx_data.img, \
	&cub3d.mlx_data.bits_per_pixel, &cub3d.mlx_data.line_length, &cub3d.mlx_data.endian);
	draw_floor_and_celling(&cub3d.mlx_data, 0x00F5F7F0, 0x00A284AB);
	mlx_put_image_to_window(cub3d.mlx_data.mlx, \
	cub3d.mlx_data.win, cub3d.mlx_data.img, 0, 0);
	find_wall(cub3d.plr, cub3d.map_data.map);
	// mlx_loop(cub3d.mlx_data.mlx);
}
