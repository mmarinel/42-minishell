/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:15:50 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/25 07:53:54 by mmarinel         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
}
