/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_operations_granular.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:26:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 15:26:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

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
