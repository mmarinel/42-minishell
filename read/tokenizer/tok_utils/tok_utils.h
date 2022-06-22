/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:04:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/22 12:40:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOK_UTILS_H
# define TOK_UTILS_H

#include "../tokenizer.h"

// * user defines TYPES

# ifndef TOK_TYPES
#  define TOK_TYPES
typedef enum e_op_code
{
	e_READ_INPUT,
	e_NEXT_TOKEN,
	e_GO_BACK,
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
	void			(*to_string)(struct s_token *token);
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_var_ass_content
{
	char						*name;
	char						*val;
	struct s_var_ass_content	*next;
}	t_var_ass_content;

# endif

// * user defined functions

/**
 * @brief this function adds the given token to the end of the current list of tokens
 * 
 * @param tokens the address of the first element in the list (optional if the list is not empty)
 * @param token the next token to store
 */
void	tok_add_back(t_token **token_list, t_token *token);
void	free_tok_list(t_token **token_list);
int		scan_alternate_invariant_spaces_quotes(char *str);

#endif
