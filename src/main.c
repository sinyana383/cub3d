/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:12:00 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/01 12:14:15 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	DEBUG(t_plr plr)
{
	printf("x - %.10f y - %.10f dir - %d\n", plr.x, plr.y, (int)(plr.dir * (180 / M_PI)) % 360);
}

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

int	exit_hook(t_cub3d *cub3d)
{
	(void)cub3d;
	exit(EXIT_SUCCESS);
}

void	move(t_plr *plr, char **map, double dir)
{
	double	next_x;
	double	next_y;

	next_x = plr->x + cos(dir) * RAY_STEP;
	next_y = plr->y - sin(dir) * RAY_STEP;
	if (!ft_strchr("NSWE0", map[(int)next_y][(int)next_x]))
		return ;
	map[(int)plr->y][(int)plr->x] = '0';
	map[(int)next_y][(int)next_x] = 'N';
	plr->x = next_x;
	plr->y = next_y;
	DEBUG(*plr);
}

// void	rotate_camera(t_plr *plr)
// {
	
// }

int	key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == W_KEY)
		move(&cub3d->plr, cub3d->map_data.map, cub3d->plr.dir);
	else if (keycode == S_KEY)
		move(&cub3d->plr, cub3d->map_data.map, cub3d->plr.dir - M_PI);
	else if (keycode == A_KEY)
		move(&cub3d->plr, cub3d->map_data.map, cub3d->plr.dir + M_PI_2);
	else if (keycode == D_KEY)
		move(&cub3d->plr, cub3d->map_data.map, cub3d->plr.dir - M_PI_2);
	else if (keycode == ESC_KEY)
		exit_hook(cub3d);
	return (0);
}

void	bonus_mouse_rotate(t_cub3d *cub3d)
{
	static int		tmp_x;
	int				x;
	int				del_x;
	int				tmp_y;

	mlx_mouse_hide();
	mlx_mouse_get_pos(cub3d->mlx_data.win, &x, &tmp_y);
	del_x = x - tmp_x;
	tmp_x = x;
	if (tmp_x > WIN_WIDTH || tmp_x < 0)
	{
		mlx_mouse_move(cub3d->mlx_data.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		tmp_x = WIN_WIDTH / 2;
	}
	cub3d->plr.dir -= (del_x * (FOV / WIN_WIDTH)) * 1;
}

int	render_next_frame(void *given_struct)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)given_struct;
	// bonus_mouse_rotate(cub3d);
	draw_floor_and_celling(&cub3d->mlx_data, 0x00FBF6E6, 0x00A284AB);
	draw_walls(cub3d);
	mlx_put_image_to_window(cub3d->mlx_data.mlx, \
	cub3d->mlx_data.win, cub3d->mlx_data.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	set_map(&cub3d, argc, argv);
	draw_walls(&cub3d);
	mlx_mouse_move(cub3d.mlx_data.win, WIN_WIDTH / 2 , WIN_HEIGHT / 2);
	mlx_hook(cub3d.mlx_data.win, 2, 0, key_hook, &cub3d);
	mlx_loop_hook(cub3d.mlx_data.mlx, render_next_frame, &cub3d);
	mlx_loop(cub3d.mlx_data.mlx);
}
