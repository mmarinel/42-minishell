/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 10:33:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

/**
 * @brief this function returns true iff command is exit or ctrl + D was hit
 * 
 * @param command 
 * @return t_bool 
 */
t_bool	asked_for_termination(char	*command)
{
	if (!command)
		return (e_true);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		return (e_true);
	return (e_false);
}

void	close_pipe(int pipe_[])
{
	close(pipe_[0]);
	close(pipe_[1]);
}

// TODO :-> Avoid Adding Duplicate Lines !
void ft_add_history(char *command)
{
	// char	quote;
	// int		quote_position;
	char	*stripped;

	if (command)
	{
		// stripped = string_strip(command, '"', e_false);
		// stripped = string_strip(stripped, '\'', e_true);
		stripped = command;
		if (str_not_empty(stripped)) // && -1 == history_search_pos(command, -1, where_history())
			add_history(command);
		// free(stripped);
	}
		// quote = take_starting_quote(command);
	// 	if (quote == '\'' || quote == '"')
	// 	{
	// 		quote_position = 0;
	// 		while (command[quote_position] != quote)
	// 			quote_position++;
	// 		stripped = string_strip(command, quote);
	// 		// free(stripped);
	// 	}
	// 	else
	// 		ft_strcpy(stripped, command, ft_strlen(command));
	// 	if (str_not_empty(stripped))
	// 			add_history(command);
	// 	free(stripped);
	// }
}
