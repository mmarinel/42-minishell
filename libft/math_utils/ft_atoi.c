/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:32:37 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:02:09 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_atoi_rec(const char *str, int *exponent);
//* end of static declarations //

int	ft_atoi(const char *str)
{
	int	e;

	return (ft_atoi_rec(str, &e));
}

static int	ft_atoi_rec(const char *str, int *exponent)
{
	int	rec_res;
	int	res;

	if (!(*str)
		|| (*str < '0' || *str > '9'))
		return (*exponent = 0);
	rec_res = ft_atoi_rec(str + 1, exponent);
	res = rec_res + ft_pow(10, *exponent) * (*str - '0');
	*exponent = *exponent + 1;
	return (res);
}
