/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:01:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/16 16:44:20 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_bool	ft_isspace(char c)
{
	return (c == 32 || (c >= '\t' && c <= '\r'));
}

char	*string_strip(char *str, char to_strip, t_bool free_input)
{
	char	*stripped;
	int		occurrences;
	int		idx_stripped;
	int		idx_input;

	if (!str)
		return (NULL);
	occurrences = str_number_occurrences(str, to_strip);
	stripped = (char *) malloc(
			(ft_strlen(str) - occurrences + 1) * sizeof(char));
	idx_stripped = 0;
	idx_input = 0;
	while (idx_input < (int)ft_strlen(str))
	{
		if (str[idx_input] != to_strip)
		{
			stripped[idx_stripped] = str[idx_input];
			idx_stripped++;
		}
		idx_input++;
	}
	if (free_input && str)
		free(str);
	stripped[idx_stripped] = '\0';
	return (stripped);
}

t_bool	str_not_empty(char *str)
{
	if (!str)
		return (e_false);
	while (*str)
	{
		if (e_false == ft_isspace(*str)
			&& *str != '\''
			&& *str != '"')
			return (e_true);
		str++;
	}
	return (e_false);
}

int	str_number_occurrences(char *str, char c)
{
	int	occurrences;

	if (!str)
		return (0);
	if (c == '\0')
		return (1);
	occurrences = 0;
	while (*str)
	{
		if (*str == c)
			occurrences++;
		str++;
	}
	return (occurrences);
}

/**
 * @brief this function returns a pointer to the starting of
 * substr sequence inside string 'str'
 * 
 * @param str 
 * @param substr 
 * @return char* 
 */
char	*take_substr(char *str, char *substr)
{
	char	*str_tmp;
	int		idx_substr;

	if (!str)
		return (NULL);
	while (*str)
	{
		str_tmp = str;
		idx_substr = 0;
		while (*str_tmp == substr[idx_substr]
			&& substr[idx_substr])
		{
			str_tmp++;
			idx_substr++;
		}
		if (substr[idx_substr] == '\0')
			return (str);
		else
			str++;
	}
	return (NULL);
}
