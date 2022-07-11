/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evento <evento@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:44:55 by evento            #+#    #+#             */
/*   Updated: 2022/07/11 13:22:23 by evento           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static	char	*take_parent_dir(char *path);

void	execute_cd(t_simple_command_node cmd)
{
	char	*path;

	{
		if (path[0] == '\0')
			path = ft_strdup(env_handler(BINDING_GET_VALUE, "HOME"));
		if (path[0] == '.')
			return ;
		if (path[0] == '..')
			path = take_parent_dir(path);
		else
			path = ft_strdup(cmd.cmd_args);
	}
	if (-1 == chdir(path))
	{
		perror("minishell cd: ");
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	}
	else
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	free(path);
}

static	char	*take_parent_dir(char *path)
{
	char	*parent_dir;
	size_t	last_slash_pos;
	size_t	offset;

	offset = 0;
	while (path[offset])
	{
		if (path[offset] == '/')
			last_slash_pos = offset;
		offset++;
	}
	if (last_slash_pos == 0)
		return (ft_strdup(env_handler(BINDING_GET_VALUE, "HOME")));
	else
		return (ft_strcpy(NULL, path, last_slash_pos + 1));
}
