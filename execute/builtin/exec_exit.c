/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:07:59 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 16:09:42 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	execute_exit_args_present(char **arguments);
static void	execute_exit_args_absent(char **arguments);
static void	exit_normally(char **arguments);
//* end of static declarations

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
	if (NULL == arguments || '\0' == arguments[0])
	{
		execute_exit_args_absent(arguments);
	}
	else
	{
		execute_exit_args_present(arguments);
	}
}

static void	execute_exit_args_absent(char **arguments)
{
	ft_splitclear(arguments);
	exit_shell(g_env.last_executed_cmd_exit_status);
}

static void	execute_exit_args_present(char **arguments)
{
	if (e_false == ft_is_digit_string(arguments[0]))
	{
		put_error(EXIT_NON_NUMERIC_ARGS_ERROR, 255, NULL);
		exit_normally(arguments);
	}
	else
	{
		if (split_len(arguments) > 1)
		{
			ft_splitclear(arguments);
			put_error(EXIT_TOO_MANY_ARGS_ERROR, 1, NULL);
		}
		else
		{
			g_env.last_executed_cmd_exit_status = ft_atoi(arguments[0]);
			exit_normally(arguments);
		}
	}
}

static void	exit_normally(char **arguments)
{
	ft_splitclear(arguments);
	exit(g_env.last_executed_cmd_exit_status);
}
