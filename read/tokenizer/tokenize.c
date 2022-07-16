/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:48:51 by earendil          #+#    #+#             */
/*   Updated: 2022/07/16 17:08:14 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	*tokenizer(char *command_line, t_op_code op_code);
static t_token	*tokenize(char	*command_line);

//* end of declarations //


/**
 * 
 * tokenizer object
 * ```
 * if command_line is not NULL and op_code is e_READ_INPUT:
 * 	->	input string is tokenized and its list of tokens stored
 * 		inside the function.
 * 
 * otherwise:
 * 		if op_code is e_NEXT_TOKEN: next token is returned
 * 		if op_code is e_GO_BACK: we go back in the list of tokens.
 * ```
 */
static void	*tokenizer(char *command_line, t_op_code op_code)
{
	static t_token	*token_list;
	static t_token	*cur_token = NULL;
	t_token			*token;

	if (op_code == e_READ_INPUT)
	{
		token_list = tokenize(command_line);
		cur_token = token_list;
	}
	if (op_code == e_NEXT_TOKEN)
	{
		token = cur_token;
		if (cur_token)
			cur_token = cur_token->next;
	}
	if (op_code == e_CLEAN)
	{
		free_tok_list(&token_list);
		cur_token = NULL;
	}
	return (token);
}

static t_token	*tokenize(char	*command_line)
{
	t_token	*token_list;

	token_list = NULL;
	if (e_false == ft_quote_occurrence_balanced(command_line))
	{
		g_env.last_executed_cmd_exit_status = 258;//EXIT_FAILURE; // 258
		put_error("Syntax Error: ",
			"quote unbalanced input string",
			NULL,
			e_false);
	}
	else
	{
		scan(command_line, &token_list);
	}
	return (token_list);
}

void	tokenizer_feed_input(char *command_line)
{
	if (command_line == NULL)
		return ;
	tokenizer(NULL, e_CLEAN);
	tokenizer(command_line, e_READ_INPUT);
}

t_token	*next_token(void)
{
	return (tokenizer(NULL, e_NEXT_TOKEN));
}

void	tokenizer_free(void)
{
	tokenizer(NULL, e_CLEAN);
}
