/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:00:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 15:45:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "env.h"

static void	*env_return_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument);
static void	*env_management_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument);
static void	*env_operations_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument);

void	*env_handler(t_env_handl_opcode opcode, void *argument)
{
	static t_bindings	*env = NULL;
	static t_bindings	*export = NULL;

	if (opcode == ENV_INITIALIZE
		|| opcode == ENV_CLEAN)
	{
		return (env_management_cases(env, export, opcode, argument));
	}
	if (opcode == ENV_RETURN
		|| opcode == EXPORT_RETURN
		|| opcode == ENV_LIST_TO_ARRAY)
	{
		return (env_return_cases(env, export, opcode, argument));
	}
	if (opcode == BINDING_UPDATE)
	{
		if (e_true == binding_exist(env, argument))
		{
			binding_over_write(env, argument);
			binding_over_write(export, argument);
		}
		else
		{
			binding_add_new(&env, argument, e_false);
			binding_add_new(&export, argument, e_true);
		}
	}
	if (opcode == BINDING_UNSET)
	{
		binding_remove(&env,((t_bindings *) argument)->var_name);
		binding_remove(&export,((t_bindings *) argument)->var_name);
	}
	if (opcode == BINDING_GET_VALUE)
	{
		return (binding_get_value(env, argument))
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

static *void	env_return_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument)
{
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
}

static *void	env_management_cases(t_bindings *env, t_bindings *export,
					t_env_handl_opcode opcode, void *argument)
{
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
}

static void	*env_operations_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument)
{
}
