/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_types.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:01:36 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/06 16:31:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_TYPES_H
# define ERROR_HANDLING_TYPES_H

typedef enum e_err_handl_opcodes
{
	EXIT_NON_NUMERIC_ARGS_ERROR,
	EXIT_TOO_MANY_ARGS_ERROR,
	NON_EXISTING_FILE,
	ARGS_ERROR,
	TOK_UNBALANCED_ERROR,
	TOK_NOT_RECOGNIZED_ERROR,
	PARSE_ERROR,
	CD_PATH_ERROR,
	EXIT_ARGS_ERROR,
	PWD_ARGS_ERROR,
	CMD_NOT_FOUND_ERROR,
	CMD_FAILED_ERROR,
}	t_err_handl_opcodes;

#endif
