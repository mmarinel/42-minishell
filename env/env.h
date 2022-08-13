/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:00:48 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 13:16:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// * user defined types //
# include "../types.h"
# include "env_types.h"
# include "../colors.h"

// * user defined modules //
# include "../utils/ft_utils.h"
# include "env_utils/env_utils.h"

void	*env_handler(t_env_handl_opcode opcode, void *argument);

#endif