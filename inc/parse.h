/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:26:30 by chawke            #+#    #+#             */
/*   Updated: 2022/10/11 13:31:36 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
#include "cub3d.h"
#include "libft.h"

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define FLOOR 0
# define CEILLING 1

typedef struct s_data
{
	int	width;
	int	height;
	int	playr;

}			t_data;

/*                     utilit                     */
int		ftp_strnstr(const char *haystack, const char *needle);
void	bad_error(char *s, char **line, int i);
int		ftp_atoi(const char *str, int *i);
int		ftp_memcmp(char *s1, char *s2, int n);

/*                 color_texture                  */
int		texture_save(char *line, char *s, int i, t_cub3d *cub);
int		where_texture(char *line, t_cub3d *cub);
int		save_color(char *line, t_cub3d *cub);

/*                  utilit_map                     */
void	clean_two_array(t_cub3d *cub, int i);
int		where_map(char *line);
char	*ft_strchrx(const char *s, char c, t_data *data);
void	wall_bug(t_cub3d *cub, int i, int j);

#endif