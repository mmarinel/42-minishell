/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 10:59:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char const *pre, char const *post,
			t_bool free_pre, t_bool free_post)
{
	size_t	pre_len;
	size_t	post_len;
	char	*s_join;

	if (!pre)
		return (gnl_strjoin(post, "", free_post, e_false));
	if (!post)
		return (gnl_strjoin(pre, "", free_pre, e_false));
	pre_len = gnl_strlen(pre);
	post_len = gnl_strlen(post);
	s_join = (char *) malloc((pre_len + post_len + 1) * sizeof(char));
	if (s_join == NULL)
		return (NULL);
	gnl_strcpy((char *) s_join, (char *) pre);
	gnl_strcpy((char *) s_join + pre_len, (char *) post);
	if (free_pre && pre)
		free((char *) pre);
	if (free_post && post)
		free((char *) post);
	return (s_join);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	gnl_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
}

void	gnl_strlcpy(char **dst, char *src, int dst_len)
{
	int	i;
	int	dstsize;

	i = 0;
	dstsize = dst_len + 1;
	*dst = (char *) malloc(dstsize * sizeof(char));
	gnl_memset(*dst, '\0', dstsize);
	while (i < dst_len && src[i])
	{
		(*dst)[i] = src[i];
		i++;
	}
	(*dst)[i] = '\0';
}

void	*gnl_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = b;
	while (i < len)
		s[i++] = c;
	return (b);
}
