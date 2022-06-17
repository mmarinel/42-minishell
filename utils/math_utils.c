/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:19:20 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 16:19:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

unsigned int		ft_pow(unsigned int m, unsigned int e)
{
	if (e == 0)
		return (1);
	return (m * ft_pow(m, e - 1));
}
