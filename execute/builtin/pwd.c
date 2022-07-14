/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:52:55 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 19:05:14 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	execute_pwd(t_simple_command_node cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cmd.cmd_args == NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		put_error("minishell at execute_pwd: ", "Illegal Arguments found",
			" --no arguments expected", e_false);
	}
	free(cwd);
}
