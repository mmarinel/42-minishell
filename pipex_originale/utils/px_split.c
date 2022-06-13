/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:53:13 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/17 22:35:00 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_utils.h"
#include <unistd.h>

static size_t	px_count_words(char *s, char c);
static int		px_get_words_len(char *s, char c, char **words_len);
static void		px_get_split(char *s, char c, char **split);
static int		px_allocate_word(char **split, size_t *word_len);

char	**px_split(char const *s, char c)
{
	size_t	size;
	char	**split;

	if (!s)
		return (NULL);
	size = px_count_words((char *) s, c);
	split = (char **) px_malloc((size + 1) * sizeof(char *));
	if (size == 0)
	{
		*split = NULL;
		return (split);
	}
	split[size] = NULL;
	if (!px_get_words_len((char *) s, c, split))
	{
		px_splitclear(split);
		px_error_handler(ENOMEM, NULL, e_false);
		return (NULL);
	}
	px_get_split((char *) s, c, split);
	return (split);
}

static size_t	px_count_words(char *s, char c)
{
	size_t	size;
	int		delim;

	delim = 0;
	if (*s != c && *s != '\0')
		size = 1;
	else
		size = 0;
	while (*s != '\0')
	{
		if (*s == c && !delim)
			delim += 1;
		else if (*s != c && delim)
		{
			size++;
			delim = 0;
		}
		s++;
	}
	return (size);
}

static int	px_get_words_len(char *s, char c, char **split)
{
	size_t	word_len;

	word_len = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (word_len > 0)
			{
				if (!px_allocate_word(split, &word_len))
					return (0);
				split++;
			}
		}
		else if (*s != c)
			word_len++;
		s++;
	}
	if (word_len > 0)
	{
		if (!px_allocate_word(split, &word_len))
			return (0);
	}
	return (1);
}

static void	px_get_split(char *s, char c, char **split)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		if (*s == c && i > 0)
		{
			i = 0;
			split++;
		}
		else if (*s != c)
		{
			*(*split + i) = *s;
			i++;
		}
		s++;
	}
}

static int	px_allocate_word(char **split, size_t *word_len)
{
	*split = (char *) px_malloc((*word_len + 1) * sizeof(char));
	*(*split + *word_len) = '\0';
	*word_len = 0;
	return (1);
}
