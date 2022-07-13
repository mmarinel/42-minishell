/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_unset_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:04:43 by earendil          #+#    #+#             */
/*   Updated: 2022/07/13 17:05:22 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	execute_unset(void)
{
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}
