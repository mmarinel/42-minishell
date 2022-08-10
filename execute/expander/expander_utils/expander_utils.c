/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/10 19:42:20 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

char	*cwd_read(void)
{
	char			*expansion;
	DIR				*cwd;
	struct dirent	*cwd_entry;

	expansion = NULL;
	cwd = opendir(".");
	if (cwd)
	{
		while (e_true)
		{
			cwd_entry = readdir(cwd);
			if (cwd_entry == NULL)
				break ;
			expansion = ft_strjoin(
				ft_strjoin(expansion, " ", e_true, e_false),
				cwd_entry->d_name,
				e_true, e_false
			);
		}
		closedir(cwd);
	}
	return (expansion);
}

char	**clean_results(char **results)
{
	char	**cleared;
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (results[i])
	{
		if ('\0' != *(results[i]))
			count++;
		i++;
	}
	cleared =  (char **) malloc((count + 1) * sizeof(char *));
	cleared[count] = NULL;
	i = 0;
	j = 0;
	while (results[i])
	{
		if ('\0' != *(results[i]))
		{
			cleared[j] = ft_strcpy(NULL, results[i], ft_strlen(results[i]));
			j++;
		}
		i++;
	}
	ft_splitclear(results);
	return (cleared);
}

/**
 * @brief this function splits the first input
 * in [segment]=[qs | rest] where qs is a quoted sequence
 * (i.e.: a string delimited by quotes or a single
 * -whitespace delimited- word).
 * 
 * @param segment 
 * @param pre_ref 
 * @param post_ref 
 * @return char the quote delimiting the quoted sequence taken from [segment]
 * or null byte if the found quoted sequence consists
 * of a single -whitespace delimited- word.
 */
char	split_quoted_sequence(char *segment,
			char **pre_ref, char **post_ref)
{
	char	enclosing_quotes;
	size_t	post_beginning;
	size_t	seg_len;

	seg_len = ft_strlen(segment);
	if (NULL == segment
		|| (segment[0] != '\'' && segment[0] != '\"'))
	{
		*pre_ref = NULL;
		*post_ref = NULL;
		enclosing_quotes = '\0';
	}
	else
	{
		post_beginning = skip_past_char(segment, 1, segment[0], +1);
		if (post_beginning == 1)
		{
			*pre_ref = ft_strdup(segment);
			*post_ref = NULL;
			return ('\0');
		}
		*pre_ref = ft_strcpy(NULL, segment + 1, post_beginning - 2);
		if (segment[post_beginning])
			*post_ref = ft_strcpy(NULL, segment + post_beginning,
				seg_len - post_beginning + 1);
		else
			*post_ref = NULL;
		enclosing_quotes = segment[0];
		free(segment);
	}
	return (enclosing_quotes);
}

char	*quote_as_string(char quote)
{
	if (quote == '\'')
		return ("\'");
	else if (quote == '\"')
		return ("\"");
	else
		return (NULL);
}
