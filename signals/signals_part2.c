/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:03:41 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 10:21:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/**
 * @brief custom SIG_IGN sig handler when using SIG_IGN macro is unfeasible.
 * 
 * @param signum 
 */
void	sig_ign(int signum)
{
	if (signum)
		;
}
