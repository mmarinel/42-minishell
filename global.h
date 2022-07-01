/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:27:24 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 08:59:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

typedef struct g_env
{
	int			last_executed_cmd_exit_status; // * $?
	t_bindings	*env;
	t_bindings	*export;
}	t_env;

t_env	g_env;