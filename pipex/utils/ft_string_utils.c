/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:54:58 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/17 22:33:53 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_utils.h"

char	*ps_concatenate_args(char *old_args, char *new_arg,
			t_boolean free_old, t_boolean free_new)
{
	char	*args_new;

	if (!old_args && !new_arg)
		return (NULL);
	if (!old_args)
	{
		px_strlcpy(&args_new, new_arg, px_strlen(new_arg) + 1);
		if (free_new)
			px_free(new_arg);
		return (args_new);
	}
	else
		args_new = px_strjoin(old_args, new_arg);
	if (free_old)
		px_free(old_args);
	if (free_new)
		px_free(new_arg);
	return (args_new);
}

size_t	px_strlcpy(char **dst, const char *src, size_t dstsize)
{
	unsigned long	i;

	if (!src || !(*src))
		return (0);
	*dst = (char *) px_malloc((px_strlen(src) + 1) * sizeof(char));
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

size_t	px_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	px_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*px_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s_join;

	if (!s1)
		return ((char *) s2);
	else if (!s2)
		return ((char *) s1);
	s1_len = px_strlen(s1);
	s2_len = px_strlen(s2);
	s_join = (char *) px_malloc((s1_len + s2_len + 1) * sizeof(char));
	return ((char *) px_memcpy(
			px_memcpy(s_join, s1, s1_len) + s1_len,
			s2,
			s2_len + 1) - s1_len);
}
