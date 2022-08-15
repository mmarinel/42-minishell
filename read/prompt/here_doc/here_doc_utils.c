/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:03:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 15:37:55 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static char		*take_next_delimiter(char *command, size_t offset);
static size_t	hdoc_read_file_name(char *str, size_t offset);
//* end of static declarations

t_bool	here_doc_line(char *command)
{
	if (!command)
		return (e_false);
	return (here_docs_count(command) > 0);
}

size_t	here_docs_count(char *command)
{
	size_t	here_docs;
	size_t	i;

	here_docs = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<')
		{
			if (command[i + 2] == '<')
				return (0);
			here_docs++;
		}
		i++;
	}
	return (here_docs);
}

char	**here_doc_take_delimiters(char *command)
{
	size_t	i;
	size_t	j;
	size_t	here_docs;
	char	**here_docs_delimiters;

	here_docs = here_docs_count(command);
	if (here_docs == 0)
		return (NULL);
	here_docs_delimiters = (char **) malloc((here_docs + 1) * sizeof(char *));
	here_docs_delimiters[here_docs] = NULL;
	j = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<'
			&& command[i + 2] != '<')
		{
			i = skip_consecutive_chars(command, (i + 2), ' ', +1);
			here_docs_delimiters[j] = take_next_delimiter(command, i);
			j++;
		}
		else
			i++;
	}
	return (here_docs_delimiters);
}

static char	*take_next_delimiter(char *command, size_t offset)
{
	char	*delimiter;
	size_t	delimiter_len;

	offset = skip_consecutive_chars(command, offset, ' ', +1);
	delimiter_len = hdoc_read_file_name(command, offset);
	delimiter = ft_strcpy(NULL, command + offset, delimiter_len);
	return (delimiter);
}

static size_t	hdoc_read_file_name(char *str, size_t offset)
{
	size_t	len_file_name;
	size_t	alphanumeric_offset;

	alphanumeric_offset = skip_consecutive_chars(str, offset, '$', +1);
	len_file_name = bash_next_word_len(str, alphanumeric_offset)
		+ (alphanumeric_offset - offset);
	if (str[offset + len_file_name] && str[offset + len_file_name] == '$')
		return (len_file_name + hdoc_read_file_name(str, offset + len_file_name));
	else
		return (len_file_name);
}
