/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddurrand <ddurrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:10:05 by ddurrand          #+#    #+#             */
/*   Updated: 2022/09/22 16:05:31 by ddurrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

int		ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
char	*ft_strchr(const char *s, int c);

#endif
