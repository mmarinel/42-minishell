/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:48:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/15 14:19:11 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(const char *fm_str, int fspec_index, va_list args,
				int *count);

//* end of static delcarations //


int	ft_printf(const char *format_string, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format_string);
	while (format_string[i])
	{
		if (format_string[i] == '%')
			i = print_format(format_string, i + 1, args, &count);
		else
			pf_write((char *)(format_string + i), &count);
		i++;
	}
	va_end(args);
	return (count);
}

static int	print_format(const char *fm_str, int fspec_index, va_list args,
				int *count)
{
	char	format_spec;

	format_spec = fm_str[fspec_index];
	if (format_spec == 'd')
		pf_case_int(va_arg(args, int), count);
	else if (format_spec == 'x')
		pf_case_hexa(va_arg(args, unsigned int), count);
	else if (format_spec == 's')
		pf_case_str(va_arg(args, char *), count);
	return (fspec_index);
}
