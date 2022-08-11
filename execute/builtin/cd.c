/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:44:55 by evento            #+#    #+#             */
/*   Updated: 2022/08/11 18:46:28 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*take_parent_dir(void);
static void	cd_error(char *path);
//* end of static declarations

void	execute_cd(t_simple_command_node cmd)
{
	char	*path;

	path = cmd.cmd_args;
	{
		if (bash_word_is_empty(path))
			path = ft_strdup(env_handler(BINDING_GET_VALUE, "HOME"));
		else if (path[0] == '.' && path[1] == '\0')
			return ;
		else if (path[0] == '.' && path[1] == '.' && path[2] == '\0')
			path = take_parent_dir();
		else
			path = ft_strdup(cmd.cmd_args);
	}
	if (-1 == chdir(path))
		cd_error(path);
	else
	{
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
		env_handler(BINDING_UPDATE, get_new_binding("PWD", path, e_false));
	}
	free(path);
}

static	char	*take_parent_dir(void)
{
	char	*cwd;
	size_t	last_slash_pos;
	size_t	offset;

	cwd = getcwd(NULL, PATH_MAX);
	last_slash_pos = 0;
	offset = 0;
	while (cwd[offset])
	{
		if (cwd[offset] == '/')
			last_slash_pos = offset;
		offset++;
	}
	if (last_slash_pos == 0)
		return (ft_strdup("/"));
	else
		return (ft_strcpy(NULL, cwd, last_slash_pos));
}

static void	cd_error(char *path)
{
	if (!path)
	{
		put_error(CD_PATH_ERROR, EXIT_FAILURE, NULL);
	}
	else
	{
		perror("minishell at execute_cd" RED);
		ft_printf(RESET);
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	}
}
