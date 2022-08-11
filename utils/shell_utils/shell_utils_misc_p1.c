/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_misc_p1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:29:04 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 11:32:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_utils.h"

void	set_error(t_status *status)
{
	*status = ERROR;
}

t_bool	ft_pending_pipe(char *command)
{
	size_t	len_command;
	size_t	tip;

	if (!command)
		return (e_false);
	else
	{
		len_command = ft_strlen(command);
		tip = skip_consecutive_chars(command, len_command - 1, ' ', -1);
		return (command[tip] == '|');
	}
}

t_bool	ft_pending_logical_op(char *command)
{
	size_t	len_command;
	size_t	tip;

	len_command = ft_strlen(command);
	if (!command || len_command < 2)
		return (e_false);
	tip = skip_consecutive_chars(command, len_command - 1, ' ', -1);
	return (
		(command[tip] == '&' && command[tip - 1] == '&')
		|| (command[tip] == '|' && command[tip - 1] == '|')
	);
}
