/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:13:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/14 08:49:13 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "../includes.h"

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strcpy(char *buf, char *src, int src_len);
char	*ft_strjoin(char *pre, char *post, t_bool free_pre, t_bool free_post);

void	*ft_malloc(size_t size);

#endif