/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:43:14 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 16:51:17 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"

static char	**return_paths(void);
static char	*return_path_name(char *cmd, char **pathlist);

// * end of declarations //

t_bool	is_path_name(char *cmd)
{
	return (take_substr(cmd, "/") != NULL);
}

char	*ft_get_cmd_name(char *cmd)
{
	char		*name;
	int			offset;
	size_t		i;

	name = NULL;
	offset = -1;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			offset = i;
		i++;
	}
	name = ft_strcpy(NULL, cmd + (offset + 1), ft_strlen(cmd) - offset);
	return (name);
}

char	*ft_get_pathname(char *cmd)
{
	t_bindings	*cur_var;
	char		**env_paths_split;
	char		*path;

	env_paths_split = return_paths();
	if (!env_paths_split)
		return (NULL);
	// while (*env_paths_split)
	// {
	// 	printf("cur_path: %s\n", *env_paths_split);
	// 	env_paths_split++;
	// }
	// exit(0);
	path = return_path_name(cmd, env_paths_split);
	printf("pathname is: %s\n", path);
	ft_splitclear(env_paths_split);
	return (path);
}

static char	**return_paths(void)
{
	t_bindings	*cur_var;

	cur_var = g_env.env;
	while (e_true)
	{
		if (!cur_var)
			return (NULL);
		// printf("val: %s\n", cur_var->var_val);
		if (0 == ft_strcmp(cur_var->var_name, "PATH"))
			break ;
		cur_var = cur_var->next;
	}
	return (ft_split(cur_var->var_val, ':'));
}

static char	*return_path_name(char *cmd, char **pathlist)
{
	char	*cur_full_name_candidate;

	if (is_path_name(cmd) == e_true
		&& access(cmd, X_OK) == 0)
			return (ft_strcpy(NULL, cmd, ft_strlen(cmd)));
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
