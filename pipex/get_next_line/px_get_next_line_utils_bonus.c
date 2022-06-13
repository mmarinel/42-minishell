/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_get_next_line_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:34:31 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 14:45:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_get_next_line_bonus.h"

char	*gnl_strjoin(char const *s1, char const *s2, size_t n)
{
	size_t	s1_len;
	char	*s_join;

	if (!s1)
		return (gnl_strjoin("", s2, n));
	s1_len = ft_strlen(s1);
	s_join = (char *) malloc((s1_len + n + 1) * sizeof(char));
	if (s_join == NULL)
		return (NULL);
	s_join = (char *) ft_memcpy(
			ft_memcpy(s_join, s1, s1_len) + s1_len,
			s2,
			n) - s1_len;
	s_join[s1_len + n] = '\0';
	return (s_join);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;
	size_t		i;

	ptr_dest = dst;
	ptr_src = src;
	i = 0;
	if (dst == NULL || src == NULL)
		return (dst);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	if (!b)
		return (NULL);
	i = 0;
	s = b;
	while (i < len)
		s[i++] = c;
	return (b);
}
