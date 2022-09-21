/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 11:40:29 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/21 16:45:34 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_and_step(int fd, char **buf)
{
	int	check;

	*buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!(*buf))
		return (-1);
	check = read(fd, (*buf), BUFFER_SIZE);
	if (check <= 0 || check > BUFFER_SIZE)
	{
		free(*buf);
		if (check > BUFFER_SIZE)
			return (-1);
		return (check);
	}
	(*buf)[check] = '\0';
	return (check);
}

int	check_rem_and_start(int fd, char **rem, char **buf)
{
	int	check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (*rem)
	{
		*buf = *rem;
		*rem = 0;
		return (1);
	}
	check = check_and_step(fd, buf);
	return (check);
}

int	check_res(char **res, char *buf, char **rem, int res_len)
{
	int		check;
	char	*old_res;

	if (!*res)
	{
		free(buf);
		return (-1);
	}
	if ((*res)[res_len - 1] == '\n')
	{
		old_res = *res;
		*res = gnl_substr(old_res, 0, res_len - 1);
		free(old_res);
		check = write_remainder(buf, rem);
		free(buf);
		if (check < 0)
		{
			free(*res);
			*res = NULL;
			return (-1);
		}
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*rem;
	char		*buf;
	int			res_len;
	int			check;

	*line = NULL;
	res_len = 0;
	check = check_rem_and_start(fd, &rem, &buf);
	while (check > 0)
	{
		*line = gnl_strjoin(*line, buf, &res_len);
		check = check_res(line, buf, &rem, res_len);
		if (check == 1)
			return (1);
		if (check == -1)
			return (-1);
		free(buf);
		check = check_and_step(fd, &buf);
	}
	if (check == 0)
		return (0);
	if (*line)
		free(*line);
	return (-1);
}
