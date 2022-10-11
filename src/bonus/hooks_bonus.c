/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:40:01 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:41:10 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_mouse_rotate(t_cub3d *cub3d)
{
	static int		tmp_x;
	int				x;
	int				del_x;
	int				tmp_y;

	// mlx_mouse_hide(); - спрятать мышку
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
