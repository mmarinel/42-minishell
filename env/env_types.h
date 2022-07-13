/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:03:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 11:25:55 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TYPES_H
# define ENV_TYPES_H

// # include "env.h"
# include "../types.h"

typedef enum e_env_hndl_opcode
{
	BINDING_UPDATE,
	BINDING_UNSET,
	BINDING_GET_VALUE,
	SET_INITIAL_SHLVL,
	ENV_RETURN,
	EXPORT_RETURN,
	INITIAL_SHLVL_RETURN,
	ENV_LIST_TO_ARRAY,
	ENV_CLEAN,
	ENV_INITIALIZE,
	_PRINT_ENV_ // * debug
}	t_env_handl_opcode;

#endif