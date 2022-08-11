/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:15:50 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 15:35:53 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/**
 * @brief handler for all signals when in main shell (no here_doc mode etc.)
 * 
 * @param signum 
 */
void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		exit(EXIT_FAILURE);
	if (signum == SIGINT)
	{
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGTERM)
	{
		exit(1);
	}
}

/**
 * @brief this function sets signal handlers
 * and disables echoing of special characters -ctr+c (^C), etc-
 * or restores it depending on [opcode] argument.
 * 
 */
void	sig_handling_set(t_sig_handling_opcode opcode)
{
	struct termios			tty_attrs_new;
	static struct termios	tty_attrs_old;

	if (opcode == SIG_INITIAL)
	{
		tcgetattr(STDIN_FILENO, &tty_attrs_old);
		tty_attrs_new = tty_attrs_old;
		tty_attrs_new.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_attrs_new);
		signal(SIGINT, sig_handler);
		signal(SIGTERM, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &tty_attrs_old);
}

/**
 * @brief EXIT_FAILURE is "thrown" for ctrl + C in line completion shell.
 * 
 * @param signum 
 */
void	line_completion_prompt_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		line_continuation_prompt(KILL, NULL, NULL, NULL);
	}
}

/**
 * @brief EXIT_FAILURE is "thrown" for ctrl + C in here_doc shell.
 * 
 * @param signum 
 */
void	here_doc_prompt_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		here_doc_prompt(KILL_HDOC, NULL, NULL);
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
