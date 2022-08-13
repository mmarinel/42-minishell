/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 17:31:36 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_utils.h"

static char	split_quoted_seq_clean_case(char **pre_ref, char **post_ref);
static char	split_quoted_seq_quotes_case(char *segment,
				char **pre_ref, char **post_ref);
//* end of static declarations

/**
 * @brief this function returns a string of entries in the current directory.
 * 
 * @return char* 
 */
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
	if (NULL == segment
		|| (segment[0] != '\'' && segment[0] != '\"'))
		return (split_quoted_seq_clean_case(pre_ref, post_ref));
	else
		return (split_quoted_seq_quotes_case(segment, pre_ref, post_ref));
}

static char	split_quoted_seq_clean_case(char **pre_ref, char **post_ref)
{
	*pre_ref = NULL;
	*post_ref = NULL;
	return ('\0');
}

static char	split_quoted_seq_quotes_case(char *segment,
				char **pre_ref, char **post_ref)
{
	char	enclosing_quotes;
	size_t	post_beginning;
	size_t	seg_len;

	seg_len = ft_strlen(segment);
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
