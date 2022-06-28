/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_misc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:29:04 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 11:36:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

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

// ! Questa cosa meglio spostarla nell'executor !!!!!!!!!
// TODO :-> put error nel prompt quando is exit = false
// TODO ma la stringa contiene exit
static t_bool	is_exit(char *command)
{
	t_bool	outcome;
	char	*stripped;
	char	quote;

	if (!command || !(*command))
		return (e_false);
	//	READING INITIAL SPACES
	command += scan_spaces(command, 0);
	// RECORDING INITIAL QUOTE
	quote = *command;
	if (quote == '"' || quote == '\'')
		command++;
	// CHECKING PRESENCE OF exit STRING
	if (!(*command) 
		|| ft_strncmp(command, "exit", 4) != 0
		|| ft_strlen(command) < 4)
		return (e_false);
	command += 4;
	// CHECKING IF INITIAL QUOTE WAS CLOSED
	if (quote == '"' || quote == '\'')
	{
		if (*command != quote)
			return (e_false);
		command++;
	}
	command += scan_invariant_quotes(command, 0);
	command += scan_spaces(command, 0);
	if (*command
		&& (e_false == bash_control_character(*command)
			|| *command == '"' || *command == '\''
			)
	)
		printf("exit: arg error\n");
	
	// command += scan_alternate_invariant_spaces_quotes(command);
	// if (*command)
	// 	printf("exit: arg error\n"); //put_error
	// exit Recognized !
	return (e_true);
}

void	close_pipe(int pipe_[])
{
	close(pipe_[0]);
	close(pipe_[1]);
}

void	set_error(t_outcome *outcome)
{
	*outcome = ERROR;
}
