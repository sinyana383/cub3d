/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:20:58 by chawke            #+#    #+#             */
/*   Updated: 2022/10/11 13:32:55 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ftp_strnstr(const char *haystack, const char *needle)
{
	int		n;
	int		x;
	int		len;

	len = ft_strlen(haystack);
	n = 0;
	x = 0;
	if (!(*needle))
		return (0);
	while (n < len && haystack[n])
	{
		while (haystack[n + x] == needle[x] && (n + x) < len)
		{
			if (!needle[x + 1])
				return (1);
			x++;
		}
		n++;
		x = 0;
	}
	return (0);
}

int	ftp_atoi(const char *str, int *i)
{
	int		resalt;

	resalt = 0;
	while (str[*i] == 32 || str[*i] == ',' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
		return (-1);
	if (str[*i] == '+' || str[*i] == '-')
		return (1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		resalt = 10 * resalt + (str[*i] - '0');
		(*i)++;
	}
	return (resalt);
}

int	ftp_memcmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	dele_n(char *line)
{
	int	i;

	i = ft_strlen(line);
	if (line[i - 1] == '\n')
		line[i - 1] = '\0';
}

void	bad_error(char *s, char **line, int i)
{
	if (i == 2)
	{
		(void)line;
		// delen_n(line);	// что делает delete_n?
	}
	write(1, "error\n", 6);
	write(1, s, ft_strlen(s));
	exit(1);
}
