/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_nbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:24:48 by earendil          #+#    #+#             */
/*   Updated: 2022/08/11 11:03:47 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	pf_put_nbr_base(long long num, const char *base,
			int base_num, int *count)
{
	if (num >= (long long) base_num)
		pf_put_nbr_base(num / base_num, base, base_num, count);
	pf_write(&base[num % base_num], count);
}
