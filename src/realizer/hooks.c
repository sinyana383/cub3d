/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:42:50 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:43:05 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_hook(t_cub3d *cub3d)
{
	int		i;
	char	**map;

	map = cub3d->map_data.map;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	exit(EXIT_SUCCESS);
}

void	move(t_plr *plr, char **map, double dir)
{
	double	next_x;
	double	next_y;

	next_x = plr->x + cos(dir) * MOVE_STEP;
	next_y = plr->y - sin(dir) * MOVE_STEP;
	if (!ft_strchr("NSWE0", map[(int)next_y][(int)next_x]))
		return ;
	map[(int)plr->y][(int)plr->x] = '0';
	map[(int)next_y][(int)next_x] = 'N';
	plr->x = next_x;
	plr->y = next_y;
}

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
	else if (keycode == LEFT_KEY)
		cub3d->plr.dir += ROT_STEP * 1;
	else if (keycode == RIGHT_KEY)
		cub3d->plr.dir += ROT_STEP * -1;
	else if (keycode == ESC_KEY)
		exit_hook(cub3d);
	return (0);
}
