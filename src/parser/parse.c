/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:09:26 by chawke            #+#    #+#             */
/*   Updated: 2022/10/11 13:49:32 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	get_height_width(char *name, t_cub3d *cub, t_data *data)
{
	int		check;
	char	*line;
	int		fd;

	check = 0;
	line = 0;
	fd = open(name, O_RDWR);
	if (fd < 0)
		exit(1);
		// bad_error("bad map", "", 1);
	get_next_line(fd, &line);
	while (line)
	{	
		if (line[0] != '\0' && !where_texture(line, cub)
			&& !save_color(line, cub))
		{
			check = ft_strlen(line) - 1;
			if (check > data->width)
				data->width = check;
			data->height++;
		}
		free(line);
		get_next_line(fd, &line);
	}
	close(fd);
}

void	fill_map(t_cub3d *cub, char *line, t_data *data)
{
	static int	i;
	int			j;

	j = 0;
	while (line[j])
	{
		if (!(ft_strchrx("1NSEW0 ", line[j], data)))
			bad_error("not allowed character", cub->map_data.map, 2);
		cub->map_data.map[i][j] = line[j];
		j++;
	}
	while (j <= data->width)
	{
		cub->map_data.map[i][j] = ' ';
		j++;
	}
	i++;
}

void	check_map(t_cub3d *cub, t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (cub->map_data.map[++j])
	{
		i = -1;
		while (cub->map_data.map[j][++i])
		{
			if ((j == 0 || j == (data->height - 1))
				&& !ft_strchr("1 ", cub->map_data.map[j][i]))
				bad_error("not surrounded by walls", cub->map_data.map, 2);
			else if (j < (data->height - 2))
			{
				if ((i == 0 || i == data->width)
					&& !(ft_strchr("1 ", cub->map_data.map[j][i])))
					bad_error("not surrounded by walls", cub->map_data.map, 2);
				else if (!(i == 0 || i == data->width)
					&& cub->map_data.map[j][i] == ' '
					&& !(j == 0 || j == data->height - 1))
					wall_bug(cub, i, j);
			}
		}
	}
}

void	get_map(t_cub3d *cub, char *name, t_data *data)
{
	int		fd;
	char	*line;

	fd = open (name, O_RDONLY);
	get_next_line(fd, &line);
	while (line)
	{
		if (!where_map(line))
		{
			fill_map(cub, line, data);
		}
		free(line);
		get_next_line(fd, &line);
	}
	check_map(cub, data);
	if (data->playr != 1)
		bad_error("bad playr", cub->map_data.map, 2);
}

void	reed_file(t_cub3d *cub, char *name)
{
	int		i;
	t_data	data;

	if (!ftp_strnstr(name, ".cub\0"))
		exit(1);
		// bad_error("bad name", "", 1);
	get_height_width(name, cub, &data);
	cub->map_data.map = (char **)malloc(sizeof(char *) * (data.height + 1));
	if (!cub->map_data.map)
		exit(1);
		// bad_error("bad memmory", "", 1);
	cub->map_data.map[data.height] = NULL;
	i = -1;
	while (++i < data.height)
	{
		cub->map_data.map[i] = (char *)malloc(sizeof(char) * (data.width + 1));
		if (!cub->map_data.map[i])
			bad_error("bad playr", cub->map_data.map, 2);
		cub->map_data.map[i][data.width + 1] = '\0';
	}	
	get_map(cub, name, &data);
}
