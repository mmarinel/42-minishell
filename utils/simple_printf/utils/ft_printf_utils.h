/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:38:22 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:03:33 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include "../ft_printf.h"

//* put_nbr_base
void				pf_put_nbr_base(long long num, const char *base,
						int base_num, int *count);

//* math utils
unsigned long long	pf_abs(long long nbr);

//* writer //
void				pf_write(const char *c, int *count);

#endif