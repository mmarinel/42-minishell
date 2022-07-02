/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_statement_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:33:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 14:42:51 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases_init.h"

t_token	*parse_statement_init(t_token *token,
	t_node_content **node_content_ref)
{
	(*node_content_ref) = (t_node_content *) malloc(sizeof(t_node_content));
	(*node_content_ref)->in_redir.file_name = NULL;
	(*node_content_ref)->out_redir.file_name = NULL;
	while (
		token->token_id == e_IN_FILE_TRUNC
		|| token->token_id == e_HERE_DOC
		|| token->token_id == e_OUT_FILE_TRUNC
		|| token->token_id == e_OUT_FILE_APPEND)
	{
		parse_redir(*node_content_ref, token->token_val, token->token_id);
		token = next_token();
		if (!token)
		{
			(*node_content_ref)->content_type = REDIR;
			break ;
			// return (new_tree_node(NULL, node_content, e_false, NULL));
		}
	}
	return (token);
}
