/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:07:59 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 17:13:21 by mmarinel         ###   ########.fr       */
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

// /**
//  * @brief this function checks for invalid arguments in the exit command node.
//  * If an error in encountered, shell status changes accordingly.
//  * 
//  * @param arguments 
//  * @return t_status: If no error is found OK is returned,
//  * otherwise ERROR is returned and shell status is set to EXIT_FAILURE.
//  */
// static t_status	exit_invalid_arguments_handling(char *arguments)
// {
// 	char		**split;
// 	t_status	outcome;

// 	if (arguments && e_false == ft_is_digit_string(arguments))
// 	{
// 		put_error(EXIT_NON_NUMERIC_ARGS_ERROR, EXIT_FAILURE, NULL);
// 		return (ERROR);
// 	}
// 	else
// 	{
// 		split = ft_split(arguments, ' ');
// 		if (split && split[0] && split[1])
// 		{
// 			put_error(EXIT_TOO_MANY_ARGS_ERROR, EXIT_FAILURE, NULL);
// 			outcome = (ERROR);
// 		}
// 		else
// 			outcome = (OK);
// 		ft_splitclear(split);
// 		return (outcome);
// 	}
// }
