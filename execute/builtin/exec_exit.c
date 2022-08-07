/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:07:59 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 17:16:34 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// static t_status	exit_invalid_arguments_handling(char *arguments);

/**
 * @brief this function exits the current shell
 * using the last executed command exit status
 * or exit status given as argument when present.
 * If an error is encountered shell status changes
 * accordingly without exiting the shell.
 * 
 * @param cmd command node of the exit command (cmd_name, cmd_args)
 */
void	execute_exit(t_simple_command_node cmd)
{
	char	**arguments;

	arguments = ft_split(cmd.cmd_args, ' ');
	if (NULL == arguments)
		exit_shell(g_env.last_executed_cmd_exit_status);
	else
	{
		if (e_false == ft_is_digit_string(arguments[0]))
		{
			put_error(EXIT_NON_NUMERIC_ARGS_ERROR, 255, NULL);
		}
		else
		{
			if (split_len(arguments) > 1)
				put_error(EXIT_TOO_MANY_ARGS_ERROR, 1, NULL);
			else
				g_env.last_executed_cmd_exit_status
					= ft_atoi(arguments[0]);
		}
	}
	ft_splitclear(arguments);
	if (1 != g_env.last_executed_cmd_exit_status)
		exit(g_env.last_executed_cmd_exit_status);
}
