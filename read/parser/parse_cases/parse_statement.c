/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_statement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:33:42 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/13 16:21:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cases.h"

static t_token	*parse_statement_redirs(t_token *token,
					t_node_content **node_content_ref,
					t_parser_status *parser_status);
//* end of static declarations

t_tree_node	*parse_statement(t_token *token, t_parser_status *parser_status)
{
	t_node_content	*node_content;

	token = parse_statement_redirs(token, &node_content, parser_status);
	if (!token)
		return (new_tree_node(NULL, node_content, NULL));
	else
	{
		if (token->token_id == e_CMD_NAME
			|| token->token_id == e_CMD_ARG)
			return (new_tree_node(NULL,
					parse_simple_command(token, node_content, parser_status),
					NULL));
		else if (token->token_id == e_ENV_VAR_DECL
			|| token->token_id == e_ENV_VAR_UNSET)
			return (new_tree_node(NULL,
					parse_env_statement(token, node_content, parser_status),
					NULL));
		ft_free(node_content->in_redir.file_name);
		ft_free(node_content->out_redir.file_name);
		free(node_content);
		return (NULL);
	}
}

static t_token	*parse_statement_redirs(t_token *token,
	t_node_content **node_content_ref, t_parser_status *parser_status)
{
	(*node_content_ref) = (t_node_content *) malloc(sizeof(t_node_content));
	// printf(YELLOW "malloc in parse_statement.c line 50: %p\n" RESET, *node_content_ref);
	// fflush(stdout);
	(*node_content_ref)->in_redir.file_name = NULL;
	(*node_content_ref)->out_redir.file_name = NULL;
	while (
		token->token_id == e_IN_FILE_TRUNC
		|| token->token_id == e_HERE_DOC
		|| token->token_id == e_OUT_FILE_TRUNC
		|| token->token_id == e_OUT_FILE_APPEND
	)
	{
		parse_redir(*node_content_ref, token->token_val, token->token_id);
		token = take_next_token(parser_status);
		if (!token)
		{
			(*node_content_ref)->content_type = REDIR;
			break ;
		}
	}
	return (token);
}
