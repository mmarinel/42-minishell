/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:07:59 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 16:40:54 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief this function exits the current shell
 * with the last executed command exit status Iff no arguments are provided.
 * 
 * @param cmd 
 */
void	execute_exit(t_simple_command_node cmd)
{
	if (cmd.cmd_args)
	{
		put_error("minishell at execute_pwd: ", "Illegal Arguments found",
			" --no arguments expected", e_false);
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	}
	else
		exit_shell(g_env.last_executed_cmd_exit_status, e_false);
}
