/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 23:52:47 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/17 23:14:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_utils.h"

static char	*ft_return_path_step2(char *cmd, char *env_paths[]);

char	*ft_return_path(char *cmd, char *const envp[])
{
	int		i;
	char	**env_paths_split;
	char	*path;

	i = 0;
	while (envp[i] && px_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	env_paths_split = px_split(envp[i] + 5, ':');
	path = ft_return_path_step2(cmd, env_paths_split);
	px_splitclear(env_paths_split);
	return (path);
}

static char	*ft_return_path_step2(char *cmd, char *env_paths[])
{
	char	*path;
	int		i;

	if (!env_paths)
		return (NULL);
	path = NULL;
	i = 0;
	while (env_paths[i])
	{	
		if (!access(path, X_OK))
			return (path);
		px_free(path);
		path = ps_concatenate_args(
				ps_concatenate_args(env_paths[i], "/", e_false, e_false),
				cmd, e_true, e_false);
		i++;
	}
	px_free(path);
	return (NULL);
}

char	*ft_get_cmd_name(char *cmd)
{
	int		offset;
	int		i;
	char	*name;

	offset = 0;
	i = 0;
	name = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			offset = i;
		else if (cmd[i] == ' ')
			break ;
		i++;
	}
	if (cmd[0] != '/')
		px_strlcpy(&name, cmd, i + 1);
	else
	{
		offset++;
		px_strlcpy(&name, cmd + offset, i - offset + 1);
	}
	return (name);
}

/**
 * @brief this function handles the specified error.
 * 
 * @param error error code to set for errno variable
 * 
 * @param strerror error string of the specified error
 * 
 * @param custom_message e_true if the strerror string 
 * is a csutom error string not to be used with perror and errno
 * 
 * 
 * @return t_boolean e_true if it has already been called in the same 
 * process.
 */
void	px_error_handler(int error, char *strerror, t_boolean custom_message)
{
	if (error != 0)
		errno = error;
	if (!custom_message)
		perror(strerror);
	else
	{
		px_putstr_fd(strerror, 2);
		free(strerror);
	}
	exit(EXIT_FAILURE);
}
