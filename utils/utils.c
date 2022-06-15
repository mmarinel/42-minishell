/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:42:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/15 21:22:43 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(EXIT_FAILURE);
	return (ptr);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

/**
 * @brief this function exits the current shell.
 * 
 * @param exit_status exit status chosen
 * @param go_on_new_line iff true, a '\ n ' gets printed before exiting.
 */
void	exit_shell(int exit_status, t_bool go_on_newline)
{
	if (go_on_newline == e_true)
		printf("\n");
	exit(exit_status);
}

/**
 * @brief This function maps points outside range [0, right_edge)
 * to points chosen as arguments.
 * 
 * @param point the point to map
 * @param right_edge the right edge of interval [0, right_edge)
 * @param left_spill_val the point where to map inputs that fall behind 0
 * @param right_spill_val the point where to map inputs that fall "above" (>=) right_edge
 * @return int the mapped point
 */
int	range_spill(int point, int right_edge, int left_spill_val, int right_spill_val)
{
	if (point < 0)
		return (left_spill_val);
	else if (point >= right_edge)
		return (right_spill_val);
	else
		return (point);
}
