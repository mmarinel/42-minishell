/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earendil <earendil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/15 18:46:41 by earendil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

static char		*get_current_working_directory(void);
static char		*get_decorated_cwd(char *cwd);
static t_bool	asked_for_termination(char	*command);
static char		*ft_readline(char *prompt, t_bool free_prompt);

char	*shell_read( char *const envp[])
{
	char	*command;

	command = ft_readline(get_current_working_directory(), e_true);
	printf("line read: %s\n", command);
	return (command);
	if (envp)
	{}
}

// ! readline library function always takes terminating '\n' off, so a new line is actually EOF (\0)
/**
 * @brief This function tries to read line until a non empty one is entered
 * or ctr + D is hit
 * 
 * @param prompt the prompt to be displayed with the readline library function.
 * @param free_prompt true if prompt needs to be freed after use
 * @return char* the next line read
 */
static char	*ft_readline(char *prompt, t_bool free_prompt)
{
	char	*command;

	command = readline(prompt);
	if (asked_for_termination(command))
		exit_shell(EXIT_SUCCESS, e_true);
	else if (*command == '\0')
		return (ft_readline(prompt, free_prompt));
	if (free_prompt)
		free(prompt);
	return (command);
}

static t_bool	asked_for_termination(char	*command)
{
	if (!command)
		return (e_true);
	else if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
			return (e_true);
	return (e_false);
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
