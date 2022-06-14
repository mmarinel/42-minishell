/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/14 17:19:47 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

static char		*get_current_working_directory(void);
static char		*get_decorated_cwd(char *cwd);
static t_bool	asked_for_termination(char	*command);
static void		exit_shell(int exit_status, char *command);

char	*shell_read( char *const envp[])
{
	char	*command;

	command = "";
	while (*command == '\0')
	{
		command = readline(get_current_working_directory());
		if (asked_for_termination(command))
			exit_shell(EXIT_SUCCESS, command);
	}
	printf("line read: %s\n", command);
	return (command);
	if (envp)
	{}
}

static t_bool	asked_for_termination(char	*command)
{

	if (!command)
		return (e_true);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
			return (e_true);
	return (e_false);
}

static	void	exit_shell(int exit_status, char *command)
{
	if (!command)
		printf("\n");
	exit(exit_status);
}

static char	*get_current_working_directory(void)
{
	char	*abs_path;
	char	*cwd;
	size_t	last_slash_idx;
	size_t	idx;

	abs_path = getcwd(NULL, PATH_MAX);
	last_slash_idx = 0;
	idx = -1;
	while (abs_path[++idx])
		if (abs_path[idx] == '/')
			last_slash_idx = idx;
	cwd = get_decorated_cwd(abs_path + last_slash_idx);
	free(abs_path);
	return (cwd);
}

// ! cwd must not to be freed as it is a shifted pointer !! 
/**
 * @brief this function returns the current working directory from the shifted
 * absolute path pointer (char *) stored in cwd.
 * 
 * @param cwd char * -: the current working directory (cwd) full path
 * shifted to the last occurrence of a '/' character
 * @return char* -: the current working directory name,
 * colored and decorated with a funny emoji
 */
static char	*get_decorated_cwd(char *cwd)
{
	return (
		ft_strjoin(
			"📁:-",
			ft_strjoin(
				ft_strjoin(MAGENTA, cwd, e_false, e_false),
				": " RESET,
				e_true,
				e_false
			),
			e_false,
			e_true
		)
	);
}
