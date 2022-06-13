/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:55:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/18 22:20:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_utils.h"
#include <stdio.h>

void	px_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	*px_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		px_error_handler(ENOMEM, NULL, e_false);
	return (ptr);
}

void	px_lstclear(t_cmd **lst, void (*del)(void *))
{
	if (!lst || !(*lst))
		return ;
	px_lstclear(&((*lst)->prev), del);
	(*lst)->prev = NULL;
	free((*lst));
	*lst = NULL;
}
