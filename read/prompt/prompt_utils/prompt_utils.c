/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:00:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/06 10:46:52 by mmarinel         ###   ########.fr       */
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
	int		cur_stdout_backup;

	readline_on_real_stdout:
	{
		cur_stdout_backup = dup(STDOUT_FILENO);
		dup2(g_env.stdout_clone, STDOUT_FILENO);
		line = readline(prompt);
		dup2(cur_stdout_backup, STDOUT_FILENO);
		close(cur_stdout_backup);
	}
	if (!line)
	ctrlD:
	{
		return (NULL);
	}
	else if (*line == '\0')
	newline://ctrlC:
	{
		free(line);
		return (ft_readline(prompt));
	}
	else
		return (line);
}
