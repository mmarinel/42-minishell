/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:35:33 by evento            #+#    #+#             */
/*   Updated: 2022/08/13 16:14:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static size_t	remove_n_option_part(char *args);
//* end of static declarations

void	execute_echo(t_simple_command_node cmd)
{
	t_bool	print_trailing_nl;
	size_t	offset;

	printf("echo args are: %s\n", cmd.cmd_args);
	offset = remove_n_option_part(cmd.cmd_args);
	{
		if (offset == 0)
			print_trailing_nl = e_true;
		else
			print_trailing_nl = e_false;
	}
	if (cmd.cmd_args)
		ft_printf("%s", cmd.cmd_args + offset);
	if (print_trailing_nl)
		ft_printf("\n");
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

/**
 * @brief this function returns the offset of the substring in [args]
 * corresponding to the argument found after the -n option.
 * 
 * @param args 
 * @return size_t 
 */
static size_t	remove_n_option_part(char *args)
{
	if (args && args[0] == '-' && args[1] == 'n')
	{
		if (e_true == ft_isspace(args[2]))
			return (2);
		else
			return (0);
	}
	else
		return (0);
}
