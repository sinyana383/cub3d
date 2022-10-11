/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chawke <chawke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:18:37 by chawke            #+#    #+#             */
/*   Updated: 2022/10/10 18:20:05 by chawke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	clean_two_array(t_cub3d *cub, int i)
{
	while (i-- > 0)
	{
		free(cub->map_data.map[i]);
	}
	free(cub->map_data.map);
	exit(1);
}

int	where_map(char *line)
{
	while (line[0] == ' ' || line[0] == '1' || line[0] == '\t')
	{
		return (0);
	}
	return (1);
}

char	*ft_strchrx(const char *s, char c, t_data *data)
{
	int		i;

	i = 0;
	if (c == 'W')
		++(data->playr);
	if (c == 'N')
		++(data->playr);
	if (c == 'S')
		++(data->playr);
	if (c == 'E')
		++(data->playr);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (((char *)s) + i);
	return (0);
}

void	wall_bug(t_cub3d *cub, int i, int j)
{
	if (!ft_strchr("1 ", cub->map_data.map[j + 1][i])
						|| !ft_strchr("1 ", cub->map_data.map[j - 1][i])
						|| !ft_strchr("1 ", cub->map_data.map[j][i + 1])
						|| !ft_strchr("1 ", cub->map_data.map[j][i - 1]))
		bad_error("not surrounded walls", cub->map_data.map, 2);
}
