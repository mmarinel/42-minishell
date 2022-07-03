/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:07:59 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 12:01:01 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// * exit esce con lo stato dell'utlimo comando eseguito.
// * se gli argomenti sono sbagliati, esce con errore.
void	execute_exit(t_simple_command_node cmd, char *simple_cmd_name)
{
	if (cmd.cmd_args)
	{
		printf("minishell at execuet_exit: invalid arguments\n");
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	}
	printf("exit\n");
	free(simple_cmd_name);
	if (g_env.last_executed_cmd_exit_status == EXIT_FAILURE)
		kill(0, SIGUSR1);
	else
		kill(0, SIGUSR2);
	exit(g_env.last_executed_cmd_exit_status);
}
