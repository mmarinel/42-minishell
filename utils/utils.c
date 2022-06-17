/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:42:56 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 09:58:36 by mmarinel         ###   ########.fr       */
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

/**
 * @brief this function returns true iff command is exit or ctrl + D was hit
 * 
 * @param command 
 * @return t_bool 
 */
t_bool	asked_for_termination(char	*command)
{
	if (!command)
		return (e_true);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		return (e_true);
	return (e_false);
}
