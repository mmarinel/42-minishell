/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:15:50 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 10:45:18 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief EXIT_FAILURE is "thrown" for ctrl + C
 * 
 * @param signum 
 */
void	prompt_line_completion_sig_handler(int signum)
{
	if (signum == SIGINT)
		exit(EXIT_FAILURE);
}
