/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/19 10:48:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "../includes.h"

// * user defines TYPES

typedef enum e_op_code
{
	e_RETURN_TOK,
	e_STORE_NXT_TOK,
	e_STORE_STR,
	e_RETURN_CUR_STR,
	e_ADVANCE_STR,
	e_CLEAN
}	t_op_code;

typedef enum e_token_id
{
	e_ARG,
	e_EXPORT,
	e_ENV_VAR_NAME,
	e_SHELL_VAR_NAME,
	e_FILENAME,
	e_USR_PROGRAM,
	e_DOUBLE_QUOTE,
	e_SINGLE_QUOTE,
	e_PARENTHESIS,
	e_OPERATOR,
	e_REDIRECT,
	e_LOGICAL,
	e_ASSIGN,
	e_PIPE,
	e_NONE
}	t_token_id;

typedef struct s_token
{
	t_token_id	token_id;
	void		*token_val;
}	t_token;

// * user defined EXPOSED FUNCTIONS

char	*shell_read( char *const envp[]);

#endif