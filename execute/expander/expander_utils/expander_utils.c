/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:45 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/09 19:09:05 by mmarinel         ###   ########.fr       */
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

size_t	parse_uninterpreted_prefix(char *segment,
			char **uninterpreted_prefix_ref)
{
	size_t	suffix_offset;

	if (segment[0] == '"' || segment[0] == '\'')
	{
		suffix_offset = skip_past_char(segment, 0 + 1, segment[0], +1);
		*uninterpreted_prefix_ref = string_strip(
			ft_strcpy(NULL, segment, suffix_offset),
			segment[0], e_true
		);
	}
	else
	{
		*uninterpreted_prefix_ref = NULL;
		suffix_offset = 0;
	}
	return (suffix_offset);
}

char	get_seg_enclosing_quote(char *segment)
{
	if (NULL == segment)
		return ('\0');
	else
	{
		if (*segment == '\'' || *segment == '\"')
		{
			printf("iushus--> %s\n", segment);
			return (*segment);
		}
		else
			return ('\0');
	}
}
