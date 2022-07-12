/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:35:33 by evento            #+#    #+#             */
/*   Updated: 2022/07/12 17:00:27 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static size_t	take_n_option(char *args);

void	execute_echo(t_simple_command_node cmd)
{
	t_bool	print_trailing_nl;
	size_t	offset;

	if (!cmd.cmd_args)
		return ;
	offset = take_n_option(cmd.cmd_args);
	{
		if (offset == 0)
			print_trailing_nl = e_true;
		else
			print_trailing_nl = e_false;
	}
	while (e_true == ft_isspace(cmd.cmd_args[offset]))
		offset++;
	printf("%s", cmd.cmd_args + offset);
	if (print_trailing_nl)
		printf("\n");
}

static size_t	take_n_option(char *args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '-' && args[i + 1] == 'n')
		{
			i += 2;
			while (args[i] == '\'' || args[i] == '"')
			{
				if (args[i + 1] != args[i])
					return (0);
				i += 2;
			}
			if (e_false == ft_isspace(args[i]))
				return (0);
			return (i);
		}
		else if (e_false == ft_isspace(args[i]))
			return (0);
		i++;
	}
	return (0);
}
