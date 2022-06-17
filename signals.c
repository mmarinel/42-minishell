/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:15:50 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 12:52:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
