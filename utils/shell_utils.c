/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:27:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 20:27:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "../read/tokenizer/tok_utils/tok_utils.h"

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
	command += scan_spaces(command);
	// RECORDING INITIAL QUOTE
	quote = *command;
	if (quote == '"' || quote == '\'')
		command++;
	// CHECKING PRESENCE OF exit STRING
	if (ft_strncmp(command, "exit", 4) != 0)
		return (e_false);
	command += 4;
	// CHECKING IF INITIAL QUOTE WAS CLOSED
	if (quote == '"' || quote == '\'')
	{
		if (*command != quote)
			return (e_false);
		command++;
	}
	command += scan_invariant_quotes(command);
	command += scan_spaces(command);
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

t_bool	bash_control_character(char c)
{
	return (
		c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == '$' || c == '`' || c == '\\' || c == '"' || c == '\''
		|| ft_isspace(c)
	);
}

// ! REMOVE FROM HERE (it's in token utils)
int	scan_alternate_invariant_spaces_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		// READING ALL INVARIANT QUOTES
		while (str[idx] == '"' || str[idx] == '\'')
		{
			if (str[idx + 1] != str[idx])
				break ;
			idx += 2;
		}
		// READING ALL FINAL SPACES
		while (str[idx])
		{
			if (e_false == ft_isspace(str[idx]))
				break ;
			idx++;
		}
		if (str[idx] != '"' && str[idx] != '\''
			&& e_false == ft_isspace(str[idx]))
			break ;
	}
	return (idx);
}

int	scan_spaces(char *str)
{
	int	idx;

	idx = 0;
	while (e_true == ft_isspace(str[idx]))
		idx++;
	return (idx);
}

int	scan_invariant_quotes(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] == '"' || str[idx] == '\'')
	{
		if (str[idx + 1] != str[idx])
			break ;
		idx += 2;
	}
	return (idx);
}
