/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 08:22:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 09:11:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

static void	print_simple_command(t_tree_node *node);
static void	print_env_statement(t_tree_node *node);
static void print_operator(t_tree_node *node);

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

void	tree_to_string(t_tree_node *root)
{
	if (!root)
	{
		// printf("HERE\n");
		return ;
	}
	if (root->content->content_type == SIMPL_CMD)
		printf("SIMPLE_CMD "); //print_simple_command(root);
	else if (root->content->content_type == ENV_STATEMENT)
		printf("ENV_STATEMENT "); //print_env_statement(root);
	else
	{
		printf("(");
		tree_to_string(root->left);
		printf("OPERATOR "); //print_operator(root);
		tree_to_string(root->right);
		printf(")");
	}
}

static void print_operator(t_tree_node *node)
{
	if (node->content->operator_node.operator == e_PIPE)
		printf(" | ");
	if (node->content->operator_node.operator == e_OR)
		printf(" || ");
	if (node->content->operator_node.operator == e_AND)
		printf(" && ");
}

static void	print_simple_command(t_tree_node *node)
{
	printf(GREEN "[cmd_name: %s, cmd_arg: %s, infile: %s, outfile: %s]" RESET, node->content->simple_cmd.cmd_name, node->content->simple_cmd.cmd_args, node->content->infile, node->content->outfile);
}

static void	print_env_statement(t_tree_node *node)
{
	// t_bindings	*binding;

	if (node->content->env_decl.set)
		printf(GREEN "[EXPORT : infile: %s, outfile: %s " RESET, node->content->infile, node->content->outfile);
	else
		printf(GREEN "[UNSET : infile: %s, outfile: %s " RESET, node->content->infile, node->content->outfile);
	// binding = node->content->env_decl.bindings;
	// while (binding)
	// {
	// 	printf("\tconcat: %d, var_name: %s, var_val: %s\t", binding->concat_mode, binding->var_name, binding->var_val);
	// 	binding = binding->next;
	// }
	// printf("]");
}

	// printf("(");
	// tree_to_string(root->left);
	// if (root->content->content_type == OPERATOR)
	// 	printf("OPERATOR ");
	// if (root->content->content_type == SIMPL_CMD)
	// 	printf("SIMPLE_CMD ");
	// if (root->content->content_type == ENV_STATEMENT)
	// 	printf("ENV_STATEMENT ");
	// tree_to_string(root->right);
	// printf(")");