/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 17:22:07 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parser_initialize(t_parser_status *parser_status);

// * end of declarations //

t_tree_node	*parse(void)
{
	t_tree_node				*tree;
	t_parser_status			parser_status;

	parser_initialize(&parser_status);
	tree = parse_cmd_list(&parser_status);
	if (parser_status.status == ERROR)
	{
		put_error(PARSE_ERROR, 258, &parser_status);
		free_tree(&tree);
		tokenizer_free(); // * meglio se la chiamo nello entry point di minishell insieme a parser_free
	}
	tree_to_string(tree);
	return (tree);
}

static void	parser_initialize(t_parser_status *parser_status)
{
	parser_status->last_read_token = NULL;
	parser_status->status = OK;
	parser_status->open.double_qquotes = 0;
	parser_status->open.quotes = 0;
	parser_status->open.parenthesis = 0;
	parser_status->last_read_tok_pos = 0;
}
