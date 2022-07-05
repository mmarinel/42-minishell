/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:00:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 15:02:37 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "env.h"

void	*env_handler(t_env_handl_opcode opcode, void *argument)
{
	static t_bindings	*env = NULL;
	static t_bindings	*export = NULL;

	if (opcode == ENV_INITIALIZE)
	{
		copy_env(&env, (char **)argument, e_false);
		copy_env(&export, (char **)argument, e_true);
	}
	if (opcode == ENV_CLEAN)
	{
		free_env(env);
		free_env(export);
		env = NULL;
		export = NULL;
	}
	if (opcode == ENV_RETURN)
	{
		return (env);
	}
	if (opcode == EXPORT_RETURN)
	{
		return (export);
	}
	if (opcode == ENV_LIST_TO_ARRAY)
	{
		return ((void *)bindings_list_to_array(env));
	}
	if (opcode == BINDING_UPDATE)
	{
		if (e_true == binding_exist(env, argument))
		{
			over_write_binding(env, argument);
			over_write_binding(export, argument);
		}
		else
		{
			add_new_binding(&env, argument, e_false);
			add_new_binding(&export, argument, e_true);
		}
	}
	if (opcode == BINDING_UNSET)
	{
		binding_remove(&env,((t_bindings *) argument)->var_name);
		binding_remove(&export,((t_bindings *) argument)->var_name);
	}
	if (opcode == BINDING_GET_VALUE)
	{
		// TODO
	}
	if (opcode == _PRINT_ENV_)
	{
		t_bindings	*bindings;
		bindings = export;
		while (bindings)
		{
			printf("%s=%s\n", bindings->var_name, bindings->var_val);
			bindings =  bindings->next;
		}
		exit(0);
	}
	return (NULL);
}
