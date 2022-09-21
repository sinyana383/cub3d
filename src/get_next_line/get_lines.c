/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:07:54 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/21 16:43:23 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_prev(char **strs, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}

void	print_error_and_exit(char *s)
{
	write(1, "Error\n", ft_strlen("Error\n"));
	if (s)
		write(1, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

char	**get_map_from_file(int fd, char *mapfile)
{
	int		size;
	int		check;
	char	**res;
	int		i;

	if (set_var_and_malloc(&size, &fd, &res, mapfile) < 0)
		return (0);
	i = -1;
	while (++i < size)
	{
		check = get_next_line(fd, &(res[i]));
		if (check < 0 || !res[i])
		{
			free_prev(res, i);
			print_error_and_exit("get_next_line error");
		}
	}
	return (res);
}
