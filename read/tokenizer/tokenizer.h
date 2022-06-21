/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/21 12:54:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../read.h"
# include "../read_utils/read_utils.h"
# include "tok_utils/tok_utils.h"

// * user defines TYPES

# ifndef TOK_TYPES
#  define TOK_TYPES
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
	e_OPT,
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

typedef struct s_var_content
{
	char	*name;
	char	*val;
}	t_var_content;

# endif

// * patterns

int	scan_env_var(char *str);
int	scan_inout_file(char *str);
int	scan_operator(char *str);
int	scan_cmd_name(char *str);
int	scan_cmd_arg(char *str);
int	scan_parenthesis(char *str);

// int	scan_shell_var(char *str);

#endif