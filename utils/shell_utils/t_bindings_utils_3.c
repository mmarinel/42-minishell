/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bindings_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:28:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 15:36:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

size_t	bindings_len(t_bindings *head)
{
	size_t	j;

	j = 0;
	while (head)
	{
		j++;
		head = head->next;
	}
	return (j);
}

t_bool	binding_exist(t_bindings *head, t_bindings *binding)
{
	t_bindings	*cur;

	cur = head;
	while (cur)
	{
		if (0 == ft_strcmp(cur->var_name, binding->var_name))
			return (e_true);
		cur = cur->next;
	}
	return (e_false);
}
