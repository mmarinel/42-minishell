/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 08:22:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/02 14:16:57 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

t_tree_node	*new_tree_node(t_tree_node *left, t_node_content *content,
				t_bool launch_subshell, t_tree_node *right)
{
	t_tree_node	*new_node;

	new_node = (t_tree_node *) malloc(sizeof(t_tree_node));
	new_node->left = left;
	new_node->content = content;
	new_node->launch_subshell = launch_subshell;
	new_node->right = right;
	return (new_node);
}

void	free_tree(t_tree_node **root_ref)
{
	t_tree_node	*root;

	root = *root_ref;
	if (!root)
		return ;
	free_tree(&(root->left));
	free_tree(&(root->right));
	ft_free(root->content->in_redir.file_name);
	ft_free(root->content->out_redir.file_name);
	free(root->content);
	free(root);
	*root_ref = NULL;
}

t_token	*take_next_token(t_parser_status *parser_status)
{
	t_token	*new_token;

	new_token = next_token();
	if (new_token)
	{
		parser_status->last_read_token = new_token;
		parser_status->last_read_tok_pos += 1;
	}
	return (new_token);
}
