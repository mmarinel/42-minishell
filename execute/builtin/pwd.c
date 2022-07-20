/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:52:55 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 10:45:35 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	execute_pwd(t_simple_command_node cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cmd.cmd_args == NULL)
	{
		ft_printf("%s\n", cwd);
	}
	else
	{
		put_error(PWD_ARGS_ERROR, EXIT_FAILURE, NULL);
	}
	free(cwd);
}
