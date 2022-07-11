/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:00:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/11 18:33:43 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "env.h"

static void	*env_return_cases(t_bindings *env, t_bindings *export,
					size_t *initial_shlvl_ref, t_env_handl_opcode opcode);
static void	*env_management_cases(t_bindings **env, t_bindings **export,
					t_env_handl_opcode opcode, void *argument);
static void	*env_operations_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument);
static void	*debug_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument); // * debug

void	*env_handler(t_env_handl_opcode opcode, void *argument)
{
	static t_bindings	*env = NULL;
	static t_bindings	*export = NULL;
	static size_t		initial_shlvl;

	if (opcode == ENV_INITIALIZE
		|| opcode == ENV_CLEAN)
	{
		env_management_cases(&env, &export, opcode, argument);
	}
	if (opcode == SET_INITIAL_SHLVL)
		initial_shlvl = ft_atoi(env_handler(BINDING_GET_VALUE, "SHLVL"));
	if (opcode == ENV_RETURN
		|| opcode == EXPORT_RETURN
		|| opcode == INITIAL_SHLVL_RETURN
		|| opcode == ENV_LIST_TO_ARRAY)
		return (env_return_cases(env, export, &initial_shlvl, opcode));
	if (opcode == BINDING_UPDATE
		|| opcode == BINDING_UNSET
		|| opcode == BINDING_GET_VALUE)
		return (env_operations_cases(env, export, opcode, argument));
	if (opcode == _PRINT_ENV_)
		return (debug_cases(env, export, opcode, argument));
	return (NULL);
}

static void	*env_return_cases(t_bindings *env, t_bindings *export,
					size_t *initial_shlvl_ref, t_env_handl_opcode opcode)
{
	if (opcode == ENV_RETURN)
	{
		return (env);
	}
	if (opcode == EXPORT_RETURN)
	{
		return (export);
	}
	if (opcode == INITIAL_SHLVL_RETURN)
	{
		return (initial_shlvl_ref);
	}
	if (opcode == ENV_LIST_TO_ARRAY)
	{
		return ((void *)bindings_list_to_array(env));
	}
	return (NULL);
}

static void	*env_management_cases(t_bindings **env_ref, t_bindings **exprt_ref,
					t_env_handl_opcode opcode, void *argument)
{
	if (opcode == ENV_INITIALIZE)
	{
		copy_env(env_ref, (char **)argument, e_false);
		copy_env(exprt_ref, (char **)argument, e_true);
	}
	if (opcode == ENV_CLEAN)
	{
		free_env(*env_ref);
		free_env(*exprt_ref);
		*env_ref = NULL;
		*exprt_ref = NULL;
	}
	return (NULL);
}

static void	*env_operations_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument)
{
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
		return (binding_get_value(env, argument));
	}
	return (NULL);
}

static void	*debug_cases(t_bindings *env, t_bindings *export,
				t_env_handl_opcode opcode, void *argument)
{
	t_bindings	*current;

	if (env && export && argument)
		;
	if (opcode == _PRINT_ENV_)
	{
		current = export;
		while (current)
		{
			printf("%s=%s\n", current->var_name, current->var_val);
			current = current->next;
		}
		// exit(0);
	}
	return (NULL);
}
