/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:01:18 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 16:55:56 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	add_update_bindings(t_bindings *head);
static void	remove_bindings(t_bindings *head);

//* end of static declarations //


void	execute_env_statement(t_env_decl_node env_statement)
{
	if (env_statement.set)
	{
		add_update_bindings(env_statement.bindings);
	}
	else
	{
		remove_bindings(env_statement.bindings);
	}
}

void	execute_export(void)
{
	t_bindings	*export;

	export = (t_bindings *) env_handler(EXPORT_RETURN, NULL);
	while (export)
	{
		if (0 != ft_strcmp(export->var_name, "_"))
		{
			printf("declare -x %s", export->var_name);
			if (export->var_val)
				printf("=\"%s\"", export->var_val);
			printf("\n");
		}
		export = export->next;
	}
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

void	execute_env(void)
{
	t_bindings	*env;

	env = (t_bindings *) env_handler(EXPORT_RETURN, NULL);
	while (env)
	{
		if (env->var_val)
		{
			printf("%s=%s\n", env->var_name, env->var_val);
		}
		env = env->next;
	}
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;

}

static void	add_update_bindings(t_bindings *head)
{
	t_bindings	*cur;

	cur = head;
	while (cur)
	{
		env_handler(BINDING_UPDATE,
			get_new_binding(cur->var_name, cur->var_val, cur->concat_mode));
		cur = cur->next;
	}
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
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
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}
