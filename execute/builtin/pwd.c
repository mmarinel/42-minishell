/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:52:55 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/15 18:05:38 by mmarinel         ###   ########.fr       */
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
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	}
	else
	{
		put_error(PWD_ARGS_ERROR, EXIT_FAILURE, NULL);
	}
	free(cwd);
}
