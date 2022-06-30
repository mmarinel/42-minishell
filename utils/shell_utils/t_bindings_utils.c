/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:18:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/30 10:26:52 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

void	add_new_binding(t_bindings **head, t_bindings *new_binding,
			t_bool in_order)
{
	t_bindings	*cursor;

	if (!(*head)
		|| in_order == e_false
		|| ft_strcmp(new_binding->var_name, (*head)->var_name) < 0)
	{
		new_binding->next = *head;
		*head = new_binding;
	}
	cursor = *head;
	while (ft_strcmp(new_binding->var_name, cursor->var_name) > 0)
		cursor = cursor->next;
	new_binding->next = cursor;
	new_binding->prev = cursor->prev;
	cursor->prev->next =  new_binding;
	cursor->prev = new_binding;
}

void	copy_env(t_bindings **head, char *const envp[], t_bool in_order)
{
	char	**split;
	char	*var_name;
	char	*var_val;

	while (*envp)
	{
		split = ft_split(*envp, '=');
		var_name = split[0];
		var_val = split[1];
		add_new_binding(head,
			new_binding(var_name, var_val, e_false),
			in_order);
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

t_bindings	*new_binding(char *var_name, char *var_val, t_bool concat_mode)
{
	t_bindings	*new_binding;

	new_binding = (t_bindings *) malloc(sizeof(t_bindings));
	new_binding->var_name = var_name;
	new_binding->var_val = var_val;
	new_binding->concat_mode = concat_mode;
	new_binding->prev = NULL;
	new_binding->next = NULL;
}

/**
 * @brief this function tries to modify the value of an existing environment variable
 * 
 * @return pointer to the over-written binding, or a NULL pointer if no such variable exist in the environment
 */
t_bindings	*over_write_binding(t_bindings *head, t_bindings *binding)
{
	t_bindings	*cursor;

	cursor = head;
	while (cursor)
	{
		if (ft_strcmp(cursor->var_name, binding->var_name) == 0)
		{
			if (binding->concat_mode == e_true)
				cursor->var_val = ft_strjoin(cursor->var_val, binding->var_val, e_true, e_false);
			else
				ft_str_replace(&(cursor->var_val), binding->var_val);
			return (cursor);
		}
		cursor = cursor->next;
	}
	return (NULL);
}
