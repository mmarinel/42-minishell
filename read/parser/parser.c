/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 13:47:06 by mmarinel         ###   ########.fr       */
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
	static t_parser_status	parser_status = (t_parser_status){
		OK, (t_groupings){0,0,0}, NULL, 0
		};
	t_tree_node				*tree;

	tree = parse_cmd_list(parse_atomic_exp(&parser_status), &parser_status);
	if (parser_status.status == ERROR)
	{
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE; // 258
		if (parser_status.last_read_token)
			printf("parser: parse error near"
				RED " %s " RESET "token at pos %d\n",
				tok_to_string(parser_status.last_read_token),
				parser_status.last_read_tok_pos);
		free_tree(&tree);
		tokenizer_free(); // * meglio se la chiamo nello entry point di minishell insieme a parser_free
		parser_initialize(&parser_status);
	}
	tree_to_string(tree);
	printf ("\n");
	return (tree);
}

static t_tree_node	*parse_atomic_exp(t_parser_status *parser_status)
{
	t_token			*token;
	t_tree_node		*parenthesised;

	token = atomic_exp_parsing_init(parser_status);
	if (!token)
		return (NULL);
	if (token->token_id == e_PARENTHESIS && *((char *)token->token_val) == '(')
	{
		parser_status->open.parenthesis += 1;
		parenthesised = parse_cmd_list(
			parse_atomic_exp(parser_status), parser_status);
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
	// t_bool		launch_subshell;

	token = cmd_list_parsing_init(parser_status);
	if (!token)
		return (current);
	else if (token->token_id == e_OPERATOR)
	{
		// launch_subshell = e_false;
		new_subtree = parse_cmd_list(
				new_tree_node(current, parse_operator(token), e_false,
					parse_atomic_exp(parser_status)),
				parser_status);
		new_subtree->launch_subshell = e_false; //launch_subshell;
		if (new_subtree->right == NULL)
			set_error(&(parser_status->status));
		return (new_subtree);
	}
	else
	{
		set_error(&(parser_status->status));
		return (current);
	}
}

		// if (*((char *)token->token_val) == '|' && *(((char *)token->token_val) + 1) != '|')
		// 	launch_subshell = e_true;
		// else
		// 	launch_subshell = e_false;

static t_tree_node	*parse_statement(t_token *token)
{
	t_node_content	*node_content;

	token = parse_statement_init(token, &node_content);
	if (!token)
		return (new_tree_node(NULL, node_content, e_false, NULL));
	else
	{
		if (token->token_id == e_CMD_NAME
			|| token->token_id == e_CMD_ARG)
			return (new_tree_node(NULL,
						parse_simple_command(token, node_content), e_false,
						NULL));
		else if (token->token_id == e_ENV_VAR_DECL
				|| token->token_id == e_ENV_VAR_UNSET)
			return (new_tree_node(NULL,
						parse_env_statement(token, node_content), e_false,
						NULL));
		ft_free(node_content->in_redir.file_name);
		ft_free(node_content->out_redir.file_name);
		free(node_content);
		return (NULL);
	}
}
