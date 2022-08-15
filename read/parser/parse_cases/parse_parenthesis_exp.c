/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis_exp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:12:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 15:58:56 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases.h"

t_node_content	*parse_parenthesis_exp(t_parser_status *parser_status)
{
	t_node_content	*paren_exp;
	t_token			*next_redir;

	paren_exp = (t_node_content *) malloc(sizeof(t_node_content));
	paren_exp->content_type = PAREN_EXP;
	paren_exp->parenthesis_node.subtree = parse_cmd_list(parser_status);
	paren_exp->parenthesis_node.in_redir.file_name = NULL;
	paren_exp->parenthesis_node.out_redir.file_name = NULL;
	paren_exp->in_redir.file_name = NULL;
	paren_exp->out_redir.file_name = NULL;
	next_redir = take_next_token(parser_status);
	while (next_redir
		&& (
			next_redir->token_id == e_IN_FILE_TRUNC
			|| next_redir->token_id == e_HERE_DOC
			|| next_redir->token_id == e_OUT_FILE_TRUNC
			|| next_redir->token_id == e_OUT_FILE_APPEND
		)
	)
	{
		parse_redir(paren_exp, next_redir->token_val, next_redir->token_id);
		next_redir = take_next_token(parser_status);
	}
	return (paren_exp);
}
