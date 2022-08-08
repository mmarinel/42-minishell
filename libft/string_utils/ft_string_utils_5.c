/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:30:11 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 17:25:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (e_true)
	{
		if (s1[i] == '\0' || s2[i] == '\0'
			|| s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_str_replace(char **str, char *new)
{
	// ! risky!!
	ft_free(*str);
	*str = ft_strdup(new);
}

size_t	skip_consecutive_chars(char *string, size_t offset,
			char to_skip, int direction)
{
	while (string[offset] == to_skip
			&& e_false == (offset == 0 && direction == -1))
		offset += direction;
	return (offset);
}

size_t	skip_past_char(char *str, size_t offset,
			char to_skip, int direction)
{
	int	i;

	i = offset;
	while (e_true)
	{
		if ((i == 0 && direction == -1)
			|| (str[i] == '\0' && direction == +1))
			return (i);
		if (str[i] == to_skip)
			return (i + direction);
		i += direction;
	}
	return (offset);
}

char	*ft_strdup(char *str)
{
	char	*duplicate;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	duplicate = (char *) malloc((len + 1) * sizeof(char));
	duplicate[len] = '\0';
	while (len - 1 >= 0)
	{
		duplicate[len - 1] = str[len - 1];
		len -= 1;
	}
 	return (duplicate); 
}
