/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:18:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 12:04:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

void	copy_env(char **envp)
{
	char	**split;
	char	*var_name;
	char	*var_val;

	while (*envp)
	{
		split = ft_split(*envp, '=');
		var_name = split[0];
		var_val = split[1];
		env_handler(BINDING_UPDATE,
			get_new_binding(var_name, var_val, e_false));
		// binding_add_new(head,
		// 	get_new_binding(var_name, var_val, e_false),
		// 	in_order);
		ft_splitclear(split);
		envp++;
	}
}

void	free_env(t_bindings *head)
{
	if (!head)
		return ;
	free_env(head->next);
	free(head->var_name);
	free(head->var_val);
}

char	**bindings_list_to_array(t_bindings *head)
{
	char		**envp;
	t_bindings	*cur;
	size_t		env_len;
	size_t		j;

	env_len = bindings_len(head);
	envp = (char **) malloc((env_len + 1) * sizeof(char *));
	envp[env_len] = NULL;
	cur = head;
	j = 0;
	while (cur)
	{
		envp[j] = ft_strjoin(
				ft_strjoin(cur->var_name, "=", e_false, e_false),
				cur->var_val,
				e_true, e_false);
		j++;
		cur = cur->next;
	}
	return (envp);
}

t_bindings	*get_new_binding(char *var_name, char *var_val, t_bool concat_mode)
{
	t_bindings	*new_binding;

	new_binding = (t_bindings *) malloc(sizeof(t_bindings));
	new_binding->var_name = ft_strdup(var_name);
	new_binding->var_val = ft_strdup(var_val);
	new_binding->concat_mode = concat_mode;
	new_binding->prev = NULL;
	new_binding->next = NULL;
	return (new_binding);
}

void	free_binding(t_bindings *binding)
{
	free(binding->var_name);
	free(binding->var_val);
	free(binding);
}
