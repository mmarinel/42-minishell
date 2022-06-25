/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:26:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/25 19:46:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tree_node	*parse_cm_list(void);

t_tree_node	*parse(void)
{
	return (parse_cm_list());
}

static t_tree_node	*parse_body(void)
{
	static t_groupings	unclosed = (t_groupings){0,0,0};

}

t_tree_node	*parse_cm_list(void)
{
	t_tree_node			*sub_tree;

	sub_tree =  NULL;
	parse_cm_list_rec(sub_tree);
	return (sub_tree);
	// root->left = parse_cmd();
	// if (cur_token()->token_id == e_OPERATOR)
}

static t_tree_node	*parse_cm_list_rec(t_tree_node *tree)
{
	t_tree_node	*operator_node;

	if (!tree)
		tree = parse_body();
	operator_node = scan_operator();
	tree = new_tree_node(tree, parse_cm_list_rec(tree));
}

/*
	root->right = parse_body();
	while (e_true)
	{
		cur_token = next_token();
		if (!cur_token)
			break ;
		if (cur_token->token_id == e_PARENTHESIS)
		{
			if (*((char *)cur_token->token_id) == ')')
			{
				if (unclosed.parenthesis)
				{
					unclosed.parenthesis--;
					return (sub_tree);
				}
				else
				{
					free_tree(sub_tree);
					return (NULL);
				}
			}
			else
			{
				unclosed.parenthesis++;
				sub_tree = new_tree_node(parse_cm_list());
			}
		}
		sub_tree = (t_tree_node *) malloc(sizeof(t_tree_node));
		// while loop scan infile
	}
}
*/
