/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:42:44 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 14:54:25 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

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
	if (!cur_binding)
		return ;
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

void	binding_add_front(t_bindings **head, t_bindings *new_binding)
{
	new_binding->next = *head;
	new_binding->prev = NULL;
	if (*head)
		(*head)->prev = new_binding;
	*head = new_binding;
}

void	binding_add_back(t_bindings **head, t_bindings *new_binding)
{
	t_bindings	*cursor;

	cursor = *head;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new_binding;
	new_binding->prev = cursor;
	new_binding->next = NULL;
}

void	binding_add_in_order(t_bindings **head, t_bindings *new_binding)
{
	t_bindings	*cursor;

	if (ft_strcmp(new_binding->var_name, (*head)->var_name) < 0)
		binding_add_front(head, new_binding);
	else
	{
		cursor = *head;
		while (ft_strcmp(new_binding->var_name, cursor->var_name) > 0)
		{
			if (!(cursor->next))
				return (binding_add_back(head, new_binding));
			cursor = cursor->next;
		}
		new_binding->next = cursor;
		new_binding->prev = cursor->prev;
		cursor->prev->next =  new_binding;
		cursor->prev = new_binding;
	}
}
