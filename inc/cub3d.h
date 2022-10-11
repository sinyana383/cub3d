/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:16:12 by ddurrand          #+#    #+#             */
/*   Updated: 2022/10/11 14:59:58 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "math.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_dda
{
	int		x_y_cur[2];
	int		x_y_steps[2];
	double	x_y_rays[2];
	double	dist;
}	t_dda;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_plr
{
	double	x;
	double	y;
	double	dir;
	double	start;
	double	end;
}	t_plr;

typedef struct s_map
{
	char		**map;
	void		*textures[4];
	int			text_w_h[2];
	int			color[2];
}	t_map;

typedef struct s_cub3d
{
	t_mlx	mlx_data;
	t_map	map_data;
	t_plr	plr;
}	t_cub3d;

// DESINES
# define WIN_WIDTH	640
# define WIN_HEIGHT	480

# define FOV 		1.0471975512
# define ROT_STEP	0.0924291465
# define MOVE_STEP	0.2

# define LEFT_KEY	123
# define RIGHT_KEY	124
# define W_KEY		13
# define A_KEY		0
# define S_KEY		1
# define D_KEY		2
# define ESC_KEY	53

void	reed_file(t_cub3d *cub, char *name);

int		key_hook(int keycode, t_cub3d *cub3d);
int		exit_hook(t_cub3d *cub3d);

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	draw_floor_and_celling(t_mlx *data, int color_celling, int color_floor);

void	find_dist_and_draw_column(t_cub3d *cub3d, int x, double main_dir);
void	draw_column(t_cub3d *cub3d, t_dda dda, int x);
void	set_img_x_and_data_tex(int *img_x, t_cub3d *cub3d, \
								double x_y_rays[2], t_mlx *data_tex);

#endif