/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 23:02:57 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 14:58:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_utils.h"

void	*px_memcpy(void *dst, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;
	size_t		i;

	ptr_dest = dst;
	ptr_src = src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

char	*px_str_replace(char **str_old, char **str_new, t_boolean free_new)
{
	if (!(*str_old))
		return (NULL);
	px_free(*str_old);
	if (!(*str_new))
		*str_old = NULL;
	else
		px_strlcpy(str_old, *str_new, px_strlen(*str_new) + 1);
	if (free_new)
		px_free(*str_new);
	return (*str_old);
}

int	px_len_split(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

void	px_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (*s != '\0')
	{
		write(fd, s, 1);
		px_putstr_fd(s + 1, fd);
	}
	else
		write(fd, "\n", 1);
}

t_boolean	px_strcmp(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (e_true);
	if (!s1 || !s2)
		return (e_false);
	while (*s1)
	{
		if (*s1 - *s2)
			return (e_false);
		s1++;
		s2++;
	}
	if (*s2 != '\n' && *s2)
		return (e_false);
	return (e_true);
}
