/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:50:02 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:50:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_TYPES_H
# define TOK_TYPES_H

# include "../../types.h"

typedef enum e_op_code
{
	e_READ_INPUT,
	e_NEXT_TOKEN,
	e_CLEAN
}	t_op_code;

typedef enum e_token_id
{
	e_CMD_NAME,
	e_CMD_ARG,
	e_IN_FILE_TRUNC,
	e_HERE_DOC,
	e_OUT_FILE_TRUNC,
	e_OUT_FILE_APPEND,
	e_OPERATOR,
	e_ENV_VAR_DECL,
	e_ENV_VAR_UNSET,
	e_SHELL_VAR_NAME,
	e_PARENTHESIS,
	e_NONE
}	t_token_id;

typedef struct s_token
{
	t_token_id		token_id;
	void			*token_val;
	void			(*to_string)(struct s_token *token);
	struct s_token	*next;
}	t_token;

#endif
