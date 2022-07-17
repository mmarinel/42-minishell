/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 18:03:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 18:09:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

t_bool	here_doc_line(char *command)
{
	if (!command)
		return (e_false);
	return (here_docs_count(command) > 0);
}

size_t	here_docs_count(char *command)
{
	size_t	i;
	size_t	here_docs;

	here_docs = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] == '<')
			return (0);
		if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] != '<')
			here_docs++;
		i++;
	}
	return (here_docs);
}

char	**here_doc_take_delimiters(char *command)
{
	size_t	i;
	size_t	j;
	size_t	here_docs;
	char	**here_docs_file_names;

	here_docs = here_docs_count(command);
	if (here_docs == 0)
		return (NULL);
	here_docs_file_names = (char **) malloc((here_docs + 1) * sizeof(char *));
	here_docs_file_names[here_docs] = NULL;
	j = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<')
		{
			i += 2;
			while (e_true == ft_isspace(command[i]))
				i++;
			here_docs_file_names[j] = take_next_word(command + i);
			j++;
		}
		else
			i++;
	}
	return (here_docs_file_names);
}
