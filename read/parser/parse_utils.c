/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 08:22:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/27 09:31:11 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree_node	*new_tree_node(t_tree_node *left, t_node_content *content, t_tree_node *right)
{
	t_tree_node	*new_node;

	new_node = (t_tree_node *) malloc(sizeof(t_tree_node));
	new_node->content = content;
	new_node->left = left;
	new_node->right = right;
}

void	free_tree(t_tree_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	ft_free(root->content->infile);
	ft_free(root->content->outfile);
	free(root->content);
	free(root);
}

t_node_content	*parse_operator(t_token *token)
{
	t_node_content	*new;

	new = (t_node_content *) malloc(sizeof(t_node_content));
	new->content_type = OPERATOR;
	new->infile = NULL;
	new->outfile = NULL;
	if (*((char *)token->token_val) == '|')
	{
		if (*((char *)token->token_val + 1) == '|')
			new->operator_node.operator = e_OR;
		else
			new->operator_node.operator = e_PIPE;
	}
	else
		new->operator_node.operator = e_AND;
	return (new);
}

t_node_content	*parse_env_decl(t_token *token)
{
	t_node_content	*new;

	new = (t_node_content *) malloc(sizeof(t_node_content));
	new->content_type = ENV_STATEMENT;
	new->infile = NULL;
	new->outfile = NULL;
	new->env_decl.set = (token->token_id == e_ENV_VAR_DECL);
	new->env_decl.bindings = (t_bindings *)token->token_val;
	token->token_val = NULL;
}

t_node_content	*parse_simple_cmd(t_token *token)
{
}
