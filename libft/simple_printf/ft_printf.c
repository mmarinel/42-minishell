/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:48:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/04 10:14:15 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(const char *fm_str, int fspec_index, va_list args,
				int *count);
static void	stdout_manage(int opcode);

//* end of static delcarations //


int	ft_printf(const char *format_string, ...)
{
	int		i;
	int		count;
	va_list	args;

	stdout_manage(PF_STDOUT_SET);
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
	stdout_manage(PF_STDOUT_RESTORE);
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

static void	stdout_manage(int opcode)
{
	if (opcode)
		;
	// static int	cur_stdout_backup;

	// if (opcode == PF_STDOUT_SET)
	// {
	// 	cur_stdout_backup = dup(STDOUT_FILENO);
	// 	dup2(STDOUT_FILENO, g_env.stdout_clone);
	// }
	// else if (opcode == PF_STDOUT_RESTORE)
	// {
	// 	dup2(cur_stdout_backup, STDOUT_FILENO);
	// 	close(cur_stdout_backup);
	// }
}
