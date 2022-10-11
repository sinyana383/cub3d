/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:09:35 by chawke            #+#    #+#             */
/*   Updated: 2022/10/11 14:11:27 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	texture_save(char *line, char *s, int i, t_cub3d *cub)
{
	int			n;

	n = 0;
	while (line[n] == ' ')
		n++;
	cub->map_data.textures[i] = mlx_xpm_file_to_image(cub->mlx_data.mlx, \
	&line[n], &cub->map_data.text_w_h[0], &cub->map_data.text_w_h[1]);
	if (!cub->map_data.textures[i])
	{
		(void)s;
		exit(1);
		// bad_error(s, "", 1);	// что писать на место ковычек? и вообще как будет все чистится?
		return (0);	// зачем return, если bad_error exit()?
	}
	else
		return (1);
}

int	where_texture(char *line, t_cub3d *cub)
{
	if (ftp_memcmp(line, "NO ", 3))
		return (texture_save(&line[3], "north texture", NO, cub));
	else if (ftp_memcmp(line, "SO ", 3))
		return (texture_save(&line[3], "south texture:", SO, cub));
	else if (ftp_memcmp(line, "WE ", 3))
		return (texture_save(&line[3], "west texture", WE, cub));
	else if (ftp_memcmp(line, "EA ", 3))
		return (texture_save(&line[3], "east texture", EA, cub));
	else
		return (0);
}

int	coloring(int n, char *line, t_cub3d *cub)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 1;
	r = ftp_atoi(&line[1], &i);
	g = ftp_atoi(&line[1], &i);
	b = ftp_atoi(&line[1], &i);
	if (r == -1 || g == -1 || b == -1 || \
		r > 255 || g > 255 || b > 255 || line[i + 1] != '\0')
		exit(1);
		// bad_error("bad color", "", 1);	// почему все bad_error не работают?
	cub->map_data.color[n] = (r * 65536) + (g * 256) + b;
	return (1);
}

int	save_color(char *line, t_cub3d *cub)
{
	if (ftp_memcmp(line, "F ", 2))
		return (coloring(FLOOR, line, cub));
	else if (ftp_memcmp(line, "C ", 2))
		return (coloring(CEILLING, line, cub));
	else
		return (0);
}
