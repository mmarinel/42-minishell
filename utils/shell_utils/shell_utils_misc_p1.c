/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_misc_p1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:29:04 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 15:19:33 by mmarinel         ###   ########.fr       */
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

void	clone_pipe(int target[2], int clone[2])
{
	clone[0] = target[0];
	clone[1] = target[1];
}

void	set_error(t_status *status)
{
	*status = ERROR;
}

/**
 * @brief this function scans the next word delimited by spaces
 * and consisting of contiguous quoted sequences
 * ending with a bash control character. 
 * (i.e.: a quoted sequence is a sequence of chars delimited by quotes
 * or a single word delimited by bash control characters except quotes)
 * 
 * @param command_line 
 * @param offset current offste inside command line
 * @return size_t the lenght of the next bash word
 */
size_t	bash_next_word_len(char *command_line, size_t offset)
{
	size_t	len_word;

	offset = skip_consecutive_chars(command_line, offset, ' ', +1);
	shifted: {
		len_word = 0;
		while (command_line[offset + len_word])
		{
			while (ft_is_quote(command_line[offset + len_word]))
					len_word = skip_past_char(
						command_line + offset,
						len_word + 1,
						command_line[offset + len_word],
						+1);
			if (command_line[offset + len_word] == '\0'
				|| e_true == bash_control_character(
							command_line[offset + len_word]))
				break ;
			len_word++;
		}
		return (len_word);
	}
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
	size_t	len_command;
	size_t	tip;

	if (!command)
		return (e_false);
	else
	{
		len_command = ft_strlen(command);
		tip = skip_consecutive_chars(command, len_command - 1, ' ', -1);
		return (command[tip] == '|');
	}
}

t_bool	ft_pending_logical_op(char *command)
{
	size_t	len_command;
	size_t	tip;

	len_command = ft_strlen(command);
	if (!command || len_command < 2)
		return (e_false);
	tip = skip_consecutive_chars(command, len_command - 1, ' ', -1);
	return (
		(command[tip] == '&' && command[tip - 1] == '&')
		|| (command[tip] == '|' && command[tip - 1] == '|')
	);
	// return (
	// 	(command[len_command - 1] == '&' && command[len_command - 2] == '&')
	// 	|| (command[len_command - 1] == '|' && command[len_command - 2] == '|')
	// );
}

t_bool	bash_word_is_empty(char *command)
{
	size_t	offset;

	if (!command)
		return (e_true);
	offset = 0;
	while (command[offset])
	{
		if (e_false == ft_isspace(command[offset]
			&& e_false == ft_is_quote(command[offset])))
			return (e_false);
		offset++;
	}
	return (e_true);
}

t_bool	command_is_empty(char *command)
{
	size_t	offset;

	if (!command)
		return (e_true);
	offset = 0;
	while (command[offset])
	{
		if (e_false == ft_isspace(command[offset]))
			return (e_false);
		offset++;
	}
	return (e_true);
}
