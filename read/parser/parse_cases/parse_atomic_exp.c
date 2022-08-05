/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_atomic_exp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:19:46 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 17:20:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases.h"

static t_token	*atomic_exp_fetch_next_token(t_parser_status *parser_status);

/**
 * @brief this function parses the next atomic expression.
 * If no atomic expression is found, a parse error is thrown.
 * 
 * @param parser_status 
 * @return t_tree_node* 
 */
t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token			*token;
	t_tree_node		*parenthesised;

	token = atomic_exp_fetch_next_token(parser_status);
	if (!token)
		return (NULL);
	if (is_open_paren(token))
	{
		parser_status->open.parenthesis += 1;
		parenthesised = new_tree_node(
			NULL,
			parse_parenthesis_exp(parser_status),
			NULL
		);
		return (parenthesised);
	}
	else
		return (parse_statement(token, parser_status));
}

static t_token	*atomic_exp_fetch_next_token(t_parser_status *parser_status)
{
	t_token	*token;

	if (parser_status->status == ERROR)
		return (NULL);
	token = take_next_token(parser_status);
	if (token == NULL
		|| is_operator_tok(token) || is_closing_paren(token))
	{
		set_error(&(parser_status->status));
		return (NULL);
	}
	return (token);
}
