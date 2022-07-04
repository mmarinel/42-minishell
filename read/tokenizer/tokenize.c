/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:48:51 by earendil          #+#    #+#             */
/*   Updated: 2022/07/04 09:44:15 by mmarinel         ###   ########.fr       */
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
	size_t	offset;
	char	*cursor;

	token_list = NULL;
	cursor = command_line;
	offset = 0;
	while (command_line[offset])
	{
		offset = scan_prologue(command_line, offset, &token_list);
		offset = scan_body(command_line, offset, &token_list);
		offset = scan_epilogue(command_line, offset, &token_list);
		if (cursor == command_line + offset)
			break ;
		cursor = command_line + offset;
	}
	if (offset < ft_strlen(command_line))
	{
		printf(RED "Syntax Error: token not recognized near " RESET GREEN "➡️ " RESET RED "%.10s...\n"
			RESET, command_line + offset);
		free_tok_list(&token_list);
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
