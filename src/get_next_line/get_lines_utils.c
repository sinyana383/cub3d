/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:20:55 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/21 16:44:28 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	reopen_file(char *file, int fd)
{
	if (close(fd) < 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	free_and_null(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

int	set_variables(int *check, char **temp, int *len, int fd)
{
	*check = get_next_line(fd, temp);
	if (*check <= 0 || !*temp)
		return (-1);
	*len = ft_strlen(*temp);
	return (1);
}

int	get_size(int fd)
{
	char	*temp;
	int		size;
	int		check;
	int		len;

	size = 0;
	if (set_variables(&check, &temp, &len, fd) < 0)
		return (-1);
	while (check >= 0 && temp)
	{
		if (len != (int)ft_strlen(temp))
		{
			free_and_null(&temp);
			return (-1);
		}
		free_and_null(&temp);
		++size;
		check = get_next_line(fd, &temp);
	}
	free_and_null(&temp);
	if (check < 0)
		return (-1);
	return (size);
}

int	set_var_and_malloc(int *size, int *fd, char ***res, char *mapfile)
{
	*size = get_size(*fd);
	if (*size < 3)
		return (-1);
	*res = malloc(sizeof(char *) * (*size) + 1);
	if (!*res)
		return (-1);
	(*res)[*size] = NULL;
	*fd = reopen_file(mapfile, *fd);
	if (*fd < 0)
	{
		free(*res);
		return (-1);
	}
	return (1);
}
