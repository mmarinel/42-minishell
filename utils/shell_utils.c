/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/20 11:03:24 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

static t_bool	is_exit(char *command);

/**
 * @brief this function returns true iff command is exit or ctrl + D was hit
 * 
 * @param command 
 * @return t_bool 
 */
t_bool	asked_for_termination(char	*command)
{
	if (!command || is_exit(command))
		return (e_true);
	return (e_false);
}

static t_bool	is_exit(char *command)
{
	t_bool	outcome;
	char	*stripped;
	char	quote;

	if (!command || !(*command))
		return (e_false);
	while (e_true == ft_isspace(*command))
		command++;
	quote = *command;
	if (quote == '"' || quote == '\'')
		command++;
	if (ft_strncmp(command, "exit", 4) != 0)
		return (e_false);
	command += 4;
	if (quote == '"' || quote == '\'')
	{
		if (*command != quote)
			return (e_false);
		command++;
	}
	while (*command == '"' || *command == '\'')
	{
		if (*(command + 1) != *command)
			return (e_false);
		command += 2;
	}
	while (*command)
	{
		if (e_false == ft_isspace(*command))
			return (e_false);
		command++;
	}
	return (e_true);
}

void	close_pipe(int pipe_[])
{
	close(pipe_[0]);
	close(pipe_[1]);
}

t_bool	bash_control_character(char c)
{
	return (
		c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == '$' || c == '`' || c == '\\' || c == '"' || c == '\''
		|| ft_isspace(c)
	);
}
