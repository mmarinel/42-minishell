/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:27:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 14:55:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct g_global
{
	int			last_executed_cmd_exit_status; // * $?
}	t_global;

t_global	g_env;

#endif