/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 15:00:32 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_cub3d *cub3d)
{
	int		i;
	double	dir;
	double	rad_step;

	dir = cub3d->plr.dir;
	cub3d->plr.start = dir + FOV / 2;
	rad_step = FOV / (WIN_WIDTH - 1);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub3d->plr.dir = cub3d->plr.start - i * rad_step;
		find_dist_and_draw_column(cub3d, i, dir);
	}
	cub3d->plr.dir = dir;
}

int	render_next_frame(void *given_struct)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)given_struct;
	draw_floor_and_celling(&cub3d->mlx_data, \
	cub3d->map_data.color[1], cub3d->map_data.color[0]);
	draw_walls(cub3d);
	mlx_put_image_to_window(cub3d->mlx_data.mlx, \
	cub3d->mlx_data.win, cub3d->mlx_data.img, 0, 0);
	return (0);
}

void	set_plr_dir(char c, double *dir)
{
	if (c == 'N')
		*dir = M_PI / 2;
	else if (c == 'W')
		*dir = M_PI;
	else if (c == 'S')
		*dir = 3 * (M_PI / 2);
	else if (c == 'E')
		*dir = 0;
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
				plr->x = (double)x + 0.5;
				plr->y = (double)y + 0.5;
				set_plr_dir(map[y][x], &plr->dir);
				plr->start = plr->dir + FOV / 2;
				plr->end = plr->dir - FOV / 2;
				return ;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	(void)argc;
	cub3d.mlx_data.mlx = mlx_init();
	reed_file(&cub3d, argv[1]);
	set_plr(cub3d.map_data.map, &cub3d.plr);
	cub3d.mlx_data.win = mlx_new_window(cub3d.mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT, "cub3d");
	cub3d.mlx_data.img = mlx_new_image(cub3d.mlx_data.mlx, \
	WIN_WIDTH, WIN_HEIGHT);
	cub3d.mlx_data.addr = mlx_get_data_addr(cub3d.mlx_data.img, \
	&cub3d.mlx_data.bits_per_pixel, \
	&cub3d.mlx_data.line_length, &cub3d.mlx_data.endian);
	draw_floor_and_celling(&cub3d.mlx_data, \
	cub3d.map_data.color[1], cub3d.map_data.color[0]);
	draw_walls(&cub3d);
	mlx_mouse_move(cub3d.mlx_data.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_hook(cub3d.mlx_data.win, 2, 0, key_hook, &cub3d);
	mlx_hook(cub3d.mlx_data.win, 17, 0, exit_hook, &cub3d);
	mlx_loop_hook(cub3d.mlx_data.mlx, render_next_frame, &cub3d);
	mlx_loop(cub3d.mlx_data.mlx);
}
