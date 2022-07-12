/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:01:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/12 15:25:24 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "builtin.h"

static void	export_print(void);
static void	add_bindings(t_bindings *head);
static void	remove_bindings(t_bindings *head);

void	execute_export(t_env_decl_node env_statement)
{
	if (env_statement.set)
	{
		if (env_statement.bindings == NULL)
			export_print();
		else
			add_bindings(env_statement.bindings);
	}
	else
	{
		remove_bindings(env_statement.bindings);
	}
	// t_bindings	*cur_binding;

	// cur_binding = root->content->env_decl.bindings;
	// while (cur_binding)
	// {
	// 	if (root->content->env_decl.set)
	// 	{
	// 		add_new_binding(&(g_env.export), cur_binding, e_true);
	// 		add_new_binding(&(g_env.env), cur_binding, e_true);
	// 	}
	// 	else
	// 	{
	// 		remove_binding(&(g_env.export), cur_binding->var_name);
	// 		remove_binding(&(g_env.env), cur_binding->var_name);
	// 	}
	// 	cur_binding = cur_binding->next;
	// }
}

static void	export_print(void)
{
}

static void	add_bindings(t_bindings *head)
{
	t_bindings	*cur;

	cur = head;
	while (cur)
	{
		env_handler(BINDING_UPDATE,
			get_new_binding(cur->var_name, cur->var_val, cur->concat_mode));
		cur = cur->next;
	}
}

static void	remove_bindings(t_bindings *head)
{
	t_bindings	*cur;

	cur = head;
	while (cur)
	{
		env_handler(BINDING_UNSET, cur);
		cur = cur->next;
	}
}
