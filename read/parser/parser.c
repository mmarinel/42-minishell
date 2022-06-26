/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/26 14:10:38 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree_node	*parse(void)
{
	static t_parser_status	parser_status = (t_parser_status){SUCCESS, (t_groupings){0,0,0}};
	t_tree_node				*tree;

	tree = parse_cmd_list(parse_atomic_exp(&parser_status), &parser_status);
	if (parser_status.status == ERROR)
	{
		free_tree(tree);
		tree = NULL;
	}
	return (tree);
}

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token	*token;

	if (parser_status->status == ERROR)
		return (NULL);
	token = next_token();
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == '(')
	{
		parser_status->open.parenthesis += 1;
		return (parse_cmd_list(parse_atomic_exp(parser_status), parser_status));
	}
	else if (token->token_id == e_CMD_NAME)
	{
		return (tree_node(parse_simple_command(token, parser_status)));
	}
	else
	{
		set_error(&(parser_status->status));
		return (NULL);
	}
}

static t_tree_node	*parse_cmd_list(t_tree_node *current,
	t_parser_status *parser_status)
{
	t_token	*token;

	if (parser_status->status == ERROR)
		return (current);
	token = next_token();
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == ')')
	{
		if (parser_status->open.parenthesis == 0)
			set_error(&(parser_status->status));
		else
			parser_status->open.parenthesis -= 1;
		return (current);
	}
	else if (token->token_id == e_OPERATOR)
	{
		return (parse_cmd_list(tree_node(current, token, parse_atomic_exp(parser_status)), parser_status));
	}
	else
	{
		set_error(&(parser_status->status));
		return (current);
	}
}
