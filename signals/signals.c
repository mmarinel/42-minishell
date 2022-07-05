/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:15:50 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 12:05:24 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/**
 * @brief handler for all
 * 
 * @param signum 
 */
void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		exit(EXIT_FAILURE);
	if (signum == SIGINT)
	{
		// printf ("in main prompt\n");
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief EXIT_FAILURE is "thrown" for ctrl + C
 * 
 * @param signum 
 */
void	line_completion_prompt_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		line_continuation_prompt(KILL, NULL, NULL);
	}
}

/**
 * 
 * shell executor signal handler
 * ```
 * if we have an exit command inside our pipeline, when execution
 * reaches it it causes the process handling the execution to kill the whole
 * process group with:
 * SIGUSR1->	indicating EXIT_SUCCESS
 * 
 * SIGUSR2->	indicating EXIT_FAILURE
 * 
 * every process will exit accordingly, including the main shell process.
 * ```
 */
void	shell_executor_handler(int signum)
{
	if (signum == SIGUSR1)
		exit(EXIT_FAILURE);
	if (signum == SIGUSR2)
		exit(EXIT_SUCCESS);
}
