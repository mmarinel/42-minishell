/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/17 11:03:54 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

static char		*get_current_working_directory(void);
static char		*get_decorated_cwd(char *cwd);
static char		*ft_readline(char *prompt, t_bool free_prompt);
// TODO :-> return EXIT CODE 258 for ctrl + D
// TODO :-> while trying to complete line (exit/errors module)
static char		*prompt_complete_line(char **command_ref);

// TODO :-> put error where exit_shell is (put error will also use exit_shell)
char	*shell_read( char *const envp[])
{
	char	*command;

	command = ft_readline(get_current_working_directory(), e_true);
	printf("line read: %s\n", command);
	return (command);
	if (envp)
		;
}

// ! readline library function always takes terminating '\n' off,
// ! so a new line is actually EOF (\0)
/**
 * @brief This function tries to read a line until a non empty-quote balanced 
 * one is entered or ctr + D is hit
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
	{
		free(command);
		return (ft_readline(prompt, free_prompt));
	}
	else if (e_false == ft_quote_occurrence_balanced(command))
	{
		command = prompt_complete_line(&command);
	}
	if (free_prompt)
		free(prompt);
	return (command);
}

// TODO :-> return EXIT CODE 258 for ctrl + D while 
// TODO trying to complete line (exit/errors module)
static char	*prompt_complete_line(char **command_ref)
{
	pid_t	new_prompt_id;
	int		new_prompt_exit_code;
	char	*continuation;

	new_prompt_id = fork();
	if (!new_prompt_id)
	{
		signal(SIGINT, prompt_line_completion_sig_handler);
		while (e_false == ft_quote_occurrence_balanced(*command_ref))
		{
			continuation = readline(">");
			if (!continuation)
				exit(EXIT_FAILURE);
			*command_ref = ft_strjoin(*command_ref, continuation, e_true, e_true
					);
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(new_prompt_id, &new_prompt_exit_code, 0);
	if (new_prompt_exit_code != EXIT_SUCCESS)
	{
		free(*command_ref);
		return (NULL);
	}
	return (*command_ref);
}

/**
 * @brief Get the current working directory (not with full path)
 * 
 * @return char* 
 */
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
		ft_strjoin
		(
			"📁:-",
			ft_strjoin
			(
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
