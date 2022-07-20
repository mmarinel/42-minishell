/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_module.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:59:13 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:06:43 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_MODULE_H
# define ERROR_HANDLING_MODULE_H

# include "../read/parser/parser_module.h"
# include "error_handling_types.h"

//* user defined exposed functions

void	put_error(t_err_handl_opcodes error_type, int error_status,
			void *argument);

#endif
