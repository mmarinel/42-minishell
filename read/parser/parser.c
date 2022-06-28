/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 17:12:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status);
static t_tree_node	*parse_cmd_list(t_tree_node *current,
						t_parser_status *parser_status);
static t_tree_node	*parse_statement(t_token *token);

// * end of declarations //


t_tree_node	*parse(void)
{
	static t_parser_status	parser_status = (t_parser_status){SUCCESS, (t_groupings){0,0,0}};
	t_tree_node				*tree;

	tree = parse_cmd_list(parse_atomic_exp(&parser_status), &parser_status);
	if (parser_status.status == ERROR)
	{
		// printf("HERE");
		fflush(stdout);
		free_tree(tree);
		tree = NULL;
	}
	tree_to_string(tree);
	printf ("\n");
	return (tree);
}

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token			*token;

	if (parser_status->status == ERROR)
		return (NULL);
	token = next_token();
	if (!token)
		return (NULL);
	if (
		token->token_id == e_OPERATOR
		||
		(
			token->token_id == e_PARENTHESIS
			&& *((char *)token->token_val) != '('
		)
	)
	{
		set_error(&(parser_status->status));
		return (NULL);
	}
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == '(')
	{
		parser_status->open.parenthesis += 1;
		return (parse_cmd_list(parse_atomic_exp(parser_status), parser_status));
	}
	else
		return (parse_statement(token));
}

static t_tree_node	*parse_cmd_list(t_tree_node *current,
	t_parser_status *parser_status)
{
	t_token	*token;

	if (parser_status->status == ERROR)
		return (current);
	token = next_token();
	if (!token)
		return (current);
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
		return (parse_cmd_list(new_tree_node(current, parse_operator(token), parse_atomic_exp(parser_status)), parser_status));
	}
	else
	{
		set_error(&(parser_status->status));
		return (current);
	}
}

static t_tree_node	*parse_statement(t_token *token)
{
	t_node_content	*node_content;

	node_content =  (t_node_content *) malloc(sizeof(t_node_content));
	node_content->infile = NULL;
	node_content->outfile = NULL;
	while (token->token_id == e_IN_FILE || token->token_id == e_OUT_FILE)
	{
		parse_redir(node_content, token->token_val, token->token_id);
		token = next_token();
		if (!token)
		{
			node_content->content_type = REDIR;
			return (new_tree_node(NULL, node_content, NULL));
		}
	}
	if (token->token_id == e_CMD_NAME || token->token_id == e_CMD_ARG)
		return (new_tree_node(NULL, parse_simple_command(token, node_content), NULL));
	else if (token->token_id == e_ENV_VAR_DECL || token->token_id == e_ENV_VAR_UNSET)
		return (new_tree_node(NULL, parse_env_statement(token, node_content), NULL));
	ft_free(node_content->infile);
	ft_free(node_content->outfile);
	free(node_content);
	return (NULL);
}
