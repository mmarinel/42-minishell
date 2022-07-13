/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:42:44 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/13 11:23:02 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

void	binding_add_new(t_bindings **head, t_bindings *new_binding,
			t_bool in_order)
{
	t_bindings	*cursor;
	t_bindings	*new_binding_copy;

	new_binding_copy = get_new_binding(
				new_binding->var_name,
				new_binding->var_val,
				new_binding->concat_mode);
	if (!(*head))
		binding_add_front(head, new_binding_copy);
	else if (in_order == e_false)
		binding_add_back(head, new_binding_copy);
	else
		binding_add_in_order(head, new_binding_copy);
}

/**
 * @brief this function tries to modify the value of an existing environment variable
 * 
 * @return pointer to the over-written binding, or a NULL pointer if no such variable exist in the environment
 */
t_bindings	*binding_over_write(t_bindings *head, t_bindings *binding)
{
	t_bindings	*cursor;
	char		*new_val;

	new_val = ft_strdup(binding->var_val);
	cursor = head;
	while (cursor)
	{
		if (ft_strcmp(cursor->var_name, binding->var_name) == 0)
		{
			if (binding->concat_mode == e_true)
				cursor->var_val =
					ft_strjoin(cursor->var_val, new_val, e_true, e_true);
			else
				ft_str_replace(&(cursor->var_val), new_val);
			return (cursor);
		}
		cursor = cursor->next;
	}
	// free(binding);
	return (NULL);
}

void	binding_remove(t_bindings **head, char *var_name)
{
	t_bindings	*cur_binding;

	cur_binding = *head;
	while (cur_binding)
	{
		if (0 == ft_strcmp(cur_binding->var_name, var_name))
			break ;
		cur_binding = cur_binding->next;
	}
	if (cur_binding)
	{
		{
			if (cur_binding->prev)
				cur_binding->prev->next = cur_binding->next;
			else
				*head = (*head)->next;
		}
		if (cur_binding->next)
		{
			cur_binding->next->prev = cur_binding->prev;
		}
		free(cur_binding->var_name);
		free(cur_binding->var_val);
		free(cur_binding);
	}
	// printf("removed?: %s\n", binding_get_value(*head, var_name));
}

/**
 * @brief this function returns the current value for the environment variable 'name'
 * 
 * @param head the head of the environment list
 * @param name the name to search
 * @return char* (always malloc-ed !) if variable is defined, its value is returned, otherwise an empty string is returned
 */
char	*binding_get_value(t_bindings *head, char *name)
{
	t_bindings	*cursor;

	cursor = head;
	while (cursor)
	{
		if (0 == ft_strcmp(cursor->var_name, name))
			return (ft_strdup(cursor->var_val));
		cursor = cursor->next;
	}
	return (NULL);//(ft_strcpy(NULL, " ", sizeof(char)));
}
