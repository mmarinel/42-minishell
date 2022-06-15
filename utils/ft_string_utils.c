/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:54:58 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/15 21:57:11 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize)
{
	unsigned long	i;

	if (!src || !(*src))
		return (0);
	*dst = (char *) ft_malloc((ft_strlen(src) + 1) * sizeof(char));
	i = 0;
	while (src[i] != '\0' && dstsize && i < (dstsize - 1))
	{
		(*dst)[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		(*dst)[i] = '\0';
	while (src[i] != '\0')
		i++;
	return ((size_t) i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		last_index;

	last_index = n - 1;
	i = 0;
	if (n == 0)
		return (0);
	while (e_true)
	{
		if (s1[i] == '\0' || s2[i] == '\0'
			|| (int)i > last_index)
			return (0);
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_strcpy(char *buf, char *src, int src_len)
{
	int	i;

	i = 0;
	while (i < src_len)
	{
		buf[i] = src[i];
		i++;
	}
}

char	*ft_strjoin(char *pre, char *post, t_bool free_pre, t_bool free_post)
{
	char	*joined;

	/// checking NULL strings
	if (!pre)
		return (ft_strjoin(post, "", free_post, e_false));
	if (!post)
		return (ft_strjoin(pre, "", free_pre, e_false));

	/// joining result
	joined = (char *) malloc(sizeof(char) * (ft_strlen(pre) + ft_strlen(post) + 1));
	joined[ft_strlen(pre) + ft_strlen(post)] = '\0';
	ft_strcpy(joined, pre, ft_strlen(pre));
	ft_strcpy(joined + ft_strlen(pre), post, ft_strlen(post));

	/// freeing memory
	if (free_pre)
		free(pre);
	if (free_post)
		free(post);

	/// returning result
	return (joined);
}
