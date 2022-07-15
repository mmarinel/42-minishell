/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:26:30 by earendil          #+#    #+#             */
/*   Updated: 2022/07/15 14:22:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_case_int(int n, int *count)
{
	if (n < 0)
		pf_write("-", count);
	pf_put_nbr_base(pf_abs(n), "0123456789", 10, count);
}

void	pf_case_hexa(long long n, int *count)
{
	pf_put_nbr_base(n, "0123456789abcdef", 16, count);
}

void	pf_case_str(char *str, int *count)
{
	size_t	i;

	if (!str)
		str = "(null)";
	i = 0;
	while (str[i])
		pf_write(str + i++, count);
}
