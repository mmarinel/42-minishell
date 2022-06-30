/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:18:17 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/30 12:27:21 by mmarinel         ###   ########.fr       */
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
		if (*head)
			(*head)->prev = new_binding;
		*head = new_binding;
	}
	else
	{
		cursor = *head;
		while (ft_strcmp(new_binding->var_name, cursor->var_name) > 0)
		{
			if (!(cursor->next))
			{
				cursor->next = new_binding;
				new_binding->prev = cursor;
				return ;
			}
			cursor = cursor->next;
		}
		new_binding->next = cursor;
		new_binding->prev = cursor->prev;
		cursor->prev->next =  new_binding;
		cursor->prev = new_binding;
		printf("HERE");
		exit(0);
	}
}

void	copy_env(t_bindings **head, char **envp, t_bool in_order)
{
	char	**split;
	char	*var_name;
	char	*var_val;

	while (*envp)
	{
		split = ft_split(*envp, '=');
		var_name = split[0]; // ! mettere ft_strcpy() e poi freeare lo split !
		var_val = split[1];
		printf("var_name: %s\n", var_name);
		printf("var_val: %s\n", var_val);
		add_new_binding(head,
			get_new_binding(var_name, var_val, e_false),
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

t_bindings	*get_new_binding(char *var_name, char *var_val, t_bool concat_mode)
{
	t_bindings	*new_binding;

	new_binding = (t_bindings *) malloc(sizeof(t_bindings));
	new_binding->var_name = var_name;
	new_binding->var_val = var_val;
	new_binding->concat_mode = concat_mode;
	new_binding->prev = NULL;
	new_binding->next = NULL;
	return (new_binding);
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
