/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:19:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/23 16:34:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

unsigned int	ft_pow(unsigned int m, unsigned int e)
{
	if (e == 0)
		return (1);
	return (m * ft_pow(m, e - 1));
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
