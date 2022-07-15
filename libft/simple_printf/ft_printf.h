/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:13:26 by earendil          #+#    #+#             */
/*   Updated: 2022/07/15 17:23:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//* system libraries //
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//* user defined modules //
# include "utils/ft_printf_utils.h"

//* includes end //


//* user defined exposed functions
int					ft_printf(const char *format_string, ...);

//* printf cases
void				pf_case_str(char *str, int *count);
void				pf_case_int(int n, int *count);
void				pf_case_hexa(long long n, int *count);

#endif