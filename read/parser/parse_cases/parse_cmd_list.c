/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:23:44 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 18:49:22 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases.h"

static t_tree_node	*parse_logical_chain(t_tree_node *current,
						t_parser_status *parser_status);
static t_tree_node	*parse_pipe_chain(t_tree_node *current,
						t_parser_status *parser_status);
static t_token		*take_next_operator_or_paren_token(
						t_parser_status *parser_status);

//* end of static declarations

t_tree_node	*parse_cmd_list(t_parser_status *parser_status)
{
	return (
		parse_logical_chain(
			parse_pipe_chain(
				parse_atomic_exp(parser_status),
				parser_status
			),
			parser_status
		)
	);
}

/**
 * @brief this function parses the whole chain of commands
 * delimited by logical operators.
 * Any pipe statements is parsed in between the logical operators.
 * 
 * @param current 
 * @param parser_status 
 * @return t_tree_node* 
 */
static t_tree_node	*parse_logical_chain(t_tree_node *current,
	t_parser_status *parser_status)
{
	t_token		*operator_or_paren_tok;
	t_tree_node	*right_subtree;

	if (parser_status->status == ERROR)
		return (current);
	operator_or_paren_tok = take_next_operator_or_paren_token(parser_status);
	if (operator_or_paren_tok == NULL)
		return (current);
	else if (operator_or_paren_tok->token_id == e_PARENTHESIS)
	{
		if (0 != ft_strcmp(operator_or_paren_tok->token_val, ")"))
			set_error(&(parser_status->status));
		return (current);
	}
	else
		return (
			parse_logical_chain(
				new_tree_node(
					current,
					parse_operator(operator_or_paren_tok, parser_status),
					parse_pipe_chain(
						parse_atomic_exp(parser_status),
						parser_status
					)
				),
				parser_status
			)
		);
}

/**
 * @brief this function parses the next pipe chain of command
 * (i.e.: atomic exp [| atomic exp...])
 * 
 * @param parser_status 
 * @return t_token* 
 */
static t_tree_node	*parse_pipe_chain(t_tree_node *current,
						t_parser_status *parser_status)
{
	t_token		*operator_tok;

	if (parser_status->status == ERROR)
		return (current);
	operator_tok = take_next_operator_or_paren_token(parser_status);
	if (operator_tok == NULL
		|| 0 != ft_strcmp(operator_tok->token_val, "|"))
	{
		if (operator_tok
			&& operator_tok->token_id != e_PARENTHESIS
			&& operator_tok->token_id != e_OPERATOR)
			set_error(&(parser_status->status));
		return (current);
	}
	else
		return (
			parse_pipe_chain(
				new_tree_node(
					current,
					parse_operator(operator_tok, parser_status),
					parse_atomic_exp(parser_status)
				),
				parser_status
			)
		);
}

/**
 * @brief this function scans the next token or returns the previous
 * one if it was an operator token.
 * 
 * @param parser_status 
 * @return t_token* 
 */
static t_token	*take_next_operator_or_paren_token(
					t_parser_status *parser_status
)
{
	if (parser_status->last_read_token
		&& (parser_status->last_read_token->token_id == e_OPERATOR
			|| parser_status->last_read_token->token_id == e_PARENTHESIS))
		return (parser_status->last_read_token);
	else
		return (take_next_token(parser_status));
}
