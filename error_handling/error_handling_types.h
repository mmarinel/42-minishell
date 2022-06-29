/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_types.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:01:36 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/29 10:37:36 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_TYPES_H
# define ERROR_HANDLING_TYPES_H

typedef enum e_err_handl_opcodes
{
	PUT_ERROR,
	GET_STATUS,
	CLEAR_ERRORS
}	t_err_handl_opcodes;

#endif
