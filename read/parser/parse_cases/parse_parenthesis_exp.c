/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis_exp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 09:12:26 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 16:50:41 by mmarinel         ###   ########.fr       */
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
	paren_exp->in_redir.file_name = NULL;
	paren_exp->out_redir.file_name = NULL;
	next_redir = take_next_token(parser_status);
	while (next_redir &&
		(
			next_redir->token_id == e_IN_FILE_TRUNC
			|| next_redir->token_id == e_HERE_DOC
			|| next_redir->token_id == e_OUT_FILE_TRUNC
			|| next_redir->token_id == e_OUT_FILE_APPEND
		)
	)
	{
		// printf("AQUI\n");
		// exit(0);
		parse_redir(paren_exp, next_redir->token_val, next_redir->token_id,
			parser_status);
		next_redir = take_next_token(parser_status);
	}
	return (paren_exp);
}
