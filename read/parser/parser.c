/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 09:34:51 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void			parser_initialize(t_parser_status *parser_status);

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status);
static t_tree_node	*parse_cmd_list(t_tree_node *current,
						t_parser_status *parser_status);
static t_tree_node	*parse_statement(t_token *token);

// * end of declarations //


t_tree_node	*parse(void)
{
	static t_parser_status	parser_status = (t_parser_status){OK, (t_groupings){0,0,0}};
	t_tree_node				*tree;

	tree = parse_cmd_list(parse_atomic_exp(&parser_status), &parser_status);
	if (parser_status.status == ERROR)
	{
		// printf("HERE")
		parser_initialize(&parser_status);
		// fflush(stdout);
		free_tree(tree);
		printf("parser: Parse error\n");
		tree = NULL;
	}
	tree_to_string(tree);
	printf ("\n");
	return (tree);
}

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token			*token;
	t_tree_node		*parenthesised;

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
		parenthesised = parse_cmd_list(parse_atomic_exp(parser_status), parser_status);
		parenthesised->launch_subshell = e_true;
		return (parenthesised);
	}
	else
		return (parse_statement(token));
}

static t_tree_node	*parse_cmd_list(t_tree_node *current,
	t_parser_status *parser_status)
{
	t_token		*token;
	t_tree_node	*new_subtree;

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
		new_subtree = parse_cmd_list(new_tree_node(current, parse_operator(token), e_false, parse_atomic_exp(parser_status)), parser_status);
		if (*((char *)token->token_val) == '|' && *((char *)token->token_val + 1) != '|')
			new_subtree->launch_subshell = e_true;
		else
			new_subtree->launch_subshell = e_false;
		return (new_subtree);
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
			return (new_tree_node(NULL, node_content, e_false, NULL));
		}
	}
	if (token->token_id == e_CMD_NAME || token->token_id == e_CMD_ARG)
		return (new_tree_node(NULL, parse_simple_command(token, node_content), e_false, NULL));
	else if (token->token_id == e_ENV_VAR_DECL || token->token_id == e_ENV_VAR_UNSET)
		return (new_tree_node(NULL, parse_env_statement(token, node_content), e_false, NULL));
	ft_free(node_content->infile);
	ft_free(node_content->outfile);
	free(node_content);
	return (NULL);
}

static void	parser_initialize(t_parser_status *parser_status)
{
	parser_status->status = OK;
	parser_status->open.double_qquotes = 0;
	parser_status->open.quotes = 0;
	parser_status->open.parenthesis = 0;
}
