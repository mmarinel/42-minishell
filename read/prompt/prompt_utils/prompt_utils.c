/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:00:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/03 19:40:47 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_utils.h"

/**
 * @brief this function adds 'command' to the history of commands 
 * iff 'command' is not an empty string or already present.
 * 
 * @param command a quote balanced command string
 * @return char** the address of the last stored entry in the history.
 */
char	**ft_add_history(char *command)
{
	static char	*last = NULL;

	if (command)
	{
		if (str_not_empty(command)
			&& (!last || 0 != ft_strcmp(last, command))
		)
		{
			add_history(command);
			ft_free(last);
			last = NULL;
			last = ft_strcpy(last, command, ft_strlen(command));
		}
	}
	return (&last);
}

/**
 * @brief this function reads a non-empty line using the readline library function.
 * If ctrl-d is hit it returns NULL.
 * 
 * @param prompt 
 * @return char* the next non-empty line read or NULL if ctr+D is hit
 */
char	*ft_readline(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		ctrlD:
		{
			// printf("AQUI!!!!!!!!!!!!\n");
			return (NULL);
		}
	else if (*line == '\0')
		ctrlC:
		{
			free(line);
			return (ft_readline(prompt));
		}
	else
		return (line);
}

char	*tee_wrap_command(char *command)
{
	return (
		ft_strjoin(
			command,
			ft_strjoin(
				" | tee ",
				get_stdout_dump_file_name(),
				e_false, e_true
			),
			e_true, e_true
		)
	);
}
