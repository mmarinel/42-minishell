/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:23:53 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 09:40:11 by mmarinel         ###   ########.fr       */
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
	e_CMD_NAME,
	e_CMD_ARG,
	e_IN_FILE,
	e_OUT_FILE,
	e_OPERATOR,
	e_ENV_VAR_ASSIGN,
	e_SHELL_VAR_NAME,
	e_PARENTHESIS,
	e_NONE
}	t_token_id;

typedef struct s_token
{
	t_token_id		token_id;
	void			*token_val;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_var_ass_content
{
	char				*name;
	char				*val;
	t_var_ass_content	*next;
}	t_var_ass_content;

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