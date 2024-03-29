/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:03:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:00:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TYPES_H
# define ENV_TYPES_H

# include "../types.h"

typedef enum e_env_hndl_opcode
{
	BINDING_UPDATE,
	BINDING_UNSET,
	BINDING_GET_VALUE,
	ENV_RETURN,
	EXPORT_RETURN,
	ENV_LIST_TO_ARRAY,
	ENV_CLEAN,
	ENV_INITIALIZE,
	_PRINT_ENV_
}	t_env_handl_opcode;

#endif