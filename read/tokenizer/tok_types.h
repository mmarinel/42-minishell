/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:50:02 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/27 09:19:15 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_TYPES_H
# define TOK_TYPES_H

typedef enum e_op_code
{
	e_READ_INPUT,
	e_NEXT_TOKEN,
	e_CUR_TOKEN,
	e_CLEAN
}	t_op_code;

typedef enum e_token_id
{
	e_CMD_NAME,
	e_CMD_ARG,
	e_IN_FILE,
	e_OUT_FILE,
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

typedef struct s_bindings
{
	t_bool				concat_mode;
	char				*var_name;
	char				*var_val;
	struct s_bindings	*next;
}	t_bindings;

#endif
