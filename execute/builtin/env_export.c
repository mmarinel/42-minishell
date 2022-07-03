/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:01:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:03:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "builtin.h"

void	execute_env_statement(t_tree_node *root, int in, int out)
{
	t_bindings	*cur_binding;

	cur_binding = root->content->env_decl.bindings;
	while (cur_binding)
	{
		if (root->content->env_decl.set)
		{
			add_new_binding(&(g_env.export), cur_binding, e_true);
			add_new_binding(&(g_env.env), cur_binding, e_true);
		}
		else
		{
			remove_binding(&(g_env.export), cur_binding, e_true);
			remove_binding(&(g_env.env), cur_binding, e_true);
		}
		cur_binding = cur_binding->next;
	}
}
