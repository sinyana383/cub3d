/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/23 17:20:15 by ddurrand         ###   ########.fr       */
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
				plr->start = plr->dir - FOV / 2;
				plr->end = plr->dir + FOV / 2;
				return ;
			}
		}
	}
}

float	ray_len(float ray, t_plr plr)
{
	float	res;
	float	cos_sin;
	int		del_x;
	int		del_y;

	cos_sin = roundf(cosf(M_PI_2) * 1000000) / 1000000;
	del_x = 
	return (res);
}

void	find_wall(t_plr plr, char **map)
{
	float	ray;
	float	cos_sin;
	int		x;
	int		y;

	ray = 0;
	x = (int)plr.x;
	y = (int)plr.y;
	while (ft_strchr("NWSE0", map[y][x]))
	{
		ray += 0.001f;
		cos_sin = roundf(cosf(plr.dir) * 1000000) / 1000000;
		x = roundf(plr.x + ray * cos_sin);
		cos_sin = roundf(sinf(plr.dir) * 1000000) / 1000000;
		y = roundf(plr.y - ray * cos_sin);
	}
	// определить какую ось по x и по y пересекли
	
	printf("angle:%f\nx - %d y - %d, ray - %f\n", \
	plr.dir * (180.0 / M_PI), x, y, ray);
}

void	find_walls(t_plr plr, char **map)
{
	int		i;
	float	dir;
	float	rad_step;

	dir = plr.dir;
	rad_step = FOV/(WIN_WIDTH-1);
	//всего выпускается WIN_WIDTH лучей, на каждый пиксель
	i = -1;
	while (++i < WIN_WIDTH)
	{
		// с каким шагом надо двигаться по углу, чтобы получилось на 640 пикселей?
		// делим 1.0472(60 град) на 640-1(отчет с нуля) частей и по этим частям ходим
		// от plr.start до plr.end
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
