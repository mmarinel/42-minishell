/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:07:59 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/06 16:47:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	invalid_arguments_handling(char *str);

/**
 * @brief this function exits the current shell
 * with the last executed command exit status Iff no arguments are provided.
 * 
 * @param cmd 
 */
void	execute_exit(t_simple_command_node cmd)
{
	if (OK == invalid_arguments_handling(cmd.cmd_args))
		exit_shell(g_env.last_executed_cmd_exit_status);
	// {
	// 	put_error(EXIT_ARGS_ERROR, EXIT_FAILURE, NULL);
	// }
	// else
	// 	exit_shell(g_env.last_executed_cmd_exit_status);
}

static t_status	invalid_arguments_handling(char *str)
{
	char		**split;
	t_status	outcome;

	if (e_false == ft_is_digit_string(str))
	{
		put_error(EXIT_NON_NUMERIC_ARGS_ERROR, EXIT_FAILURE, NULL);
		outcome = (ERROR);
	}
	else
	{
		split = ft_split(str, ' ');
		if (split && split[0] && split[1])
		{
			put_error(EXIT_TOO_MANY_ARGS_ERROR, EXIT_FAILURE, NULL);
			outcome = (ERROR);
		}
		else
			outcome = (OK);
		ft_splitclear(split);
	}
	return (outcome);
}
