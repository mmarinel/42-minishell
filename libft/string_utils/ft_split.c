/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:53:13 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 16:24:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_count_words(char *s, char c);
static void		allocate_words(char *str, char delimiter, char **split);
static void		ft_get_split(char *str, char delimiter, char **split);
//* end of static declarations

char	**ft_split(char const *string, char delimiter)
{
	size_t	words;
	char	**split;

	if (!string)
		return (NULL);
	words = ft_count_words((char *) string, delimiter);
	split = (char **) ft_malloc((words + 1) * sizeof(char *));
	// printf(YELLOW "malloc in ft_split.c line 29: %p\n" RESET, split);
	// fflush(stdout);
	split[words] = NULL;
	allocate_words((char *)string, delimiter, split);
	ft_get_split((char *) string, delimiter, split);
	return (split);
}

static size_t	ft_count_words(char *str, char delimiter)
{
	size_t	words;
	t_bool	next_word_found;

	next_word_found = e_false;
	words = 0;
	while (*str != '\0')
	{
		if (*str != delimiter && next_word_found == e_false)
		{
			words++;
			next_word_found = e_true;
		}
		else if (*str == delimiter)
		{
			next_word_found = e_false;
		}
		str++;
	}
	return (words);
}

static void	allocate_words(char *str, char delimiter, char **split)
{
	size_t	word_len;

	if (!str || !(*split))
		return ;
	word_len = 0;
	while (e_true)
	{
		if (*str == delimiter || *str == '\0')
		{
			if (word_len > 0)
			{
				*split = (char *) ft_malloc((word_len + 1) * sizeof(char));
				// printf(YELLOW "malloc in ft_split.c line 73: %p\n" RESET, *split);
				// fflush(stdout);
				(*split)[word_len] = '\0';
				word_len = 0;
				split++;
			}
		}
		else
			word_len++;
		if (*str == '\0')
			break ;
		str++;
	}
}

static void	ft_get_split(char *str, char delimiter, char **split)
{
	int		split_substr_idx;

	if (!str || !(*split))
		return ;
	split_substr_idx = 0;
	while (*str != '\0')
	{
		if (*str == delimiter && split_substr_idx > 0)
		{
			split_substr_idx = 0;
			split++;
		}
		else if (*str != delimiter)
		{
			*(*split + split_substr_idx) = *str;
			split_substr_idx++;
		}
		str++;
	}
}
