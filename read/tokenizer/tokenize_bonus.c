/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:48:51 by earendil          #+#    #+#             */
/*   Updated: 2022/06/22 10:59:14 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	*tokenizer(char *command_line, t_op_code op_code);
static t_token	*tokenize(char	*str);

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
	static	t_token	*next_token = NULL;

	if (op_code == e_READ_INPUT)
		token_list = tokenize(command_line);
	if (op_code == e_NEXT_TOKEN)
	{
		if (!next_token)
			next_token = token_list;
		else
			next_token = next_token->next;
	}
	if (op_code == e_GO_BACK)
	{
		if (!next_token)
			next_token = token_list;
		else
			next_token = next_token->prev;
	}
	if (op_code == e_CLEAN)
		free_tok_list(token_list);
	return (next_token);
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

void	tok_go_back(void)
{
	tokenizer(NULL, e_GO_BACK);
}

static t_token	*tokenize(char	*str)
{
	size_t	offset;
	t_token	*token_list;

	offset = 0;
	while (*str)
	{
		str += scan_parenthesis(str, token_list);
		str += scan_in_out_file_toks(str, token_list);
		str += scan_var(str, token_list);
		str += scan_in_out_file_toks(str, token_list);
		str += scan_cmd_name(str, token_list);
		str += scan_in_out_file_toks(str, token_list);
		str += scan_cmd_arg(str, token_list);
		str += scan_in_out_file_toks(str, token_list);
		str += scan_parenthesis(str, token_list);
		str += scan_operator(str, token_list);
	}
	tok_add_back(&token_list, NULL);
	return (token_list);
}
