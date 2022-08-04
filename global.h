/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:27:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 09:19:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct g_global
{
	pid_t			pid;//* $$
	int			last_executed_cmd_exit_status;// * $?
	int			stdout_clone;
}	t_global;

t_global	g_env;

#endif