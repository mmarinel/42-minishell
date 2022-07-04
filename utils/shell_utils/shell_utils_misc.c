/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_misc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:29:04 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 18:50:41 by mmarinel         ###   ########.fr       */
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

	if (!(*command) 
		|| ft_strncmp(command, "exit", 4) != 0
		|| ft_strlen(command) < 4)
		return (e_false);
	// if (!command || !(*command))
	// 	return (e_false);
	// //	READING INITIAL SPACES
	// command += scan_spaces(command, 0);
	// // RECORDING INITIAL QUOTE
	// quote = *command;
	// if (quote == '"' || quote == '\'')
	// 	command++;
	// // CHECKING PRESENCE OF exit STRING
	// if (!(*command) 
	// 	|| ft_strncmp(command, "exit", 4) != 0
	// 	|| ft_strlen(command) < 4)
	// 	return (e_false);
	// command += 4;
	// // CHECKING IF INITIAL QUOTE WAS CLOSED
	// if (quote == '"' || quote == '\'')
	// {
	// 	if (*command != quote)
	// 		return (e_false);
	// 	command++;
	// }
	// command += scan_invariant_quotes(command, 0);
	// command += scan_spaces(command, 0);
	// if (*command
	// 	&& (e_false == bash_control_character(*command)
	// 		|| *command == '"' || *command == '\''
	// 		)
	// )
	// 	printf("exit: arg error\n");
	
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

void	set_error(t_status *status)
{
	*status = ERROR;
}

/**
 * @brief this function checks for unquoted illegal characters in the minishell
 * project assuming command is a quote balanced string.
 * 
 * @param command 
 * @return t_bool true iff \ (backslash) and ` (backtick)
 * appear unquoted or in "" (double quotes)
 * or ; appears unquoted
 */
t_bool	minishell_illegal_chars(char *command)
{
	size_t	idx;
	t_bool	in_single_quote;
	t_bool	in_double_quote;

	in_double_quote = e_false;
	in_single_quote = e_false;
	idx = 0;
	while (command[idx])
	{
		if (command[idx] == '"' && in_single_quote == e_false)
			flip(&in_double_quote);
		if (command[idx] == '\'' && in_double_quote == e_false)
			flip(&in_single_quote);
		{
			if ((command[idx] == '\\' || command[idx] == '`')
				&& e_false == in_single_quote)
				return (e_true);
			else if (command[idx] == ';'
					&& in_double_quote == e_false
					&& in_double_quote == e_false)
				return (e_true);
		}
		idx++;
	}
	return (e_false);
}

t_bool	ft_pending_pipe(char *command)
{
	if (!command)
		return (e_false);
	else
		return (command[ft_strlen(command) - 1] == '|');
}
