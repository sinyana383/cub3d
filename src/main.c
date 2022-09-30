/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/30 12:39:40 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_cub3d *cub3d)
{
	int		i;
	double	dir;
	double	rad_step;

	dir = cub3d->plr.dir;
	rad_step = FOV / (WIN_WIDTH - 1);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub3d->plr.dir = cub3d->plr.start - i * rad_step;
		find_dist_and_draw_column(cub3d, i, dir);
	}
	cub3d->plr.dir = dir;
}

int	exit_hook(t_cub3d *cub3d)
{
	(void)cub3d;
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == 53)
		exit_hook(cub3d);
	return (0);
}

int	render_next_frame(void *given_struct)
{
	t_cub3d	*cub3d;
	int		tmp_x;
	int		tmp_y;

	cub3d = (t_cub3d *)given_struct;
	mlx_mouse_get_pos(cub3d->mlx_data.win, &tmp_x, &tmp_y);
	printf("x - %d, y - %d\n", tmp_x, tmp_y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	set_map(&cub3d, argc, argv);
	draw_walls(&cub3d);
	mlx_put_image_to_window(cub3d.mlx_data.mlx, \
	cub3d.mlx_data.win, cub3d.mlx_data.img, 0, 0);
	mlx_hook(cub3d.mlx_data.win, 2, 0, key_hook, &cub3d);
	mlx_loop_hook(cub3d.mlx_data.mlx, render_next_frame, &cub3d);
	mlx_loop(cub3d.mlx_data.mlx);
}
