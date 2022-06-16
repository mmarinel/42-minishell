/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:42:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/16 17:08:18 by mmarinel         ###   ########.fr       */
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
 * @brief This function maps points outside range [0, right_edge)
 * to points chosen as arguments.
 * 
 * @param point the point to map
 * @param right_edge the right edge of interval [0, right_edge)
 * @param left_spill_val the point where to map inputs that fall behind 0
 * @param right_spill_val the point where to map inputs that 
 * fall "above" (>=) right_edge
 * @return int the mapped point
 */
int	range_spill(int point, int right_edge,
		int left_spill_val, int right_spill_val)
{
	if (point < 0)
		return (left_spill_val);
	else if (point >= right_edge)
		return (right_spill_val);
	else
		return (point);
}
