/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:43:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 17:54:46 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"

static char	**return_paths(void);
static char	*return_path_name(char *cmd, char **pathlist);
// * end of declarations //

void	dup_std_fd(int cur_in_out, int std_in_out,
			t_bool close_cur)
{
	if (cur_in_out != std_in_out)
	{
		dup2(cur_in_out, std_in_out);
		if (close_cur)
			close(cur_in_out);
	}
}

char	*ft_get_cmd_name(char *cmd)
{
	char		*name;
	int			slash_idx;
	size_t		i;

	if (!cmd)
		return (NULL);
	name = NULL;
	slash_idx = -1;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			slash_idx = i;
		i++;
	}
	name = ft_strcpy(
			NULL,
			cmd + (slash_idx + 1),
			ft_strlen(cmd) - (slash_idx + 1)
			);
	return (name);
}

char	*ft_get_pathname(char *cmd)
{
	t_bindings	*cur_var;
	char		**env_paths_split;
	char		*path;

	if (!cmd)
		return (NULL);
	env_paths_split = return_paths();
	if (!env_paths_split)
		return (NULL);
	path = return_path_name(cmd, env_paths_split);
	ft_splitclear(env_paths_split);
	return (path);
}

static char	**return_paths(void)
{
	char	*paths;

	paths = (char *) env_handler(BINDING_GET_VALUE, "PATH");
	return (ft_split(paths, ':'));
}

static char	*return_path_name(char *cmd, char **pathlist)
{
	char	*cur_full_name_candidate;

	if (is_path_name(cmd) == e_true
		&& access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (*pathlist)
	{
		cur_full_name_candidate
			= ft_strjoin(
				ft_strjoin(*pathlist, "/", e_false, e_false),
				cmd,
				e_true, e_false);
		if (access(cur_full_name_candidate, X_OK) == 0)
			return (cur_full_name_candidate);
		free(cur_full_name_candidate);
		pathlist++;
	}
	return (NULL);
}
