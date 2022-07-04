/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 19:44:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char		*get_decorated_cwd(char *cwd);

//									perche gli altri non devono essere gestiti
// TODO :-> fare line completion anche con {`, &, pipe, (, \} --> {&, pipe, (}
// * alert 1
// ! readline library function always takes terminating '\n' off,
// ! so a new line is actually EOF (\0)
// * alert 2
// ! non empty means NO CHAR present except '\0'
// ! (i.e.: a string full of spaces is not considered empty!)
/**
 * @brief This function tries to read a line until a non empty-quote balanced 
 * one is entered or ctr + D is hit.
 * Here_Doc is managed too.
 * 
 * @param prompt the prompt to be displayed with the readline library function.
 * @param free_prompt true iff prompt needs to be freed after use
 * @return char* the next line read
 * (except here_doc content which is put in a hidden file for later use)
 */
char	*ft_readline(char *prompt, t_bool free_prompt)
{
	char	*command;

	command = readline(prompt);
	if (!command)
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	else
		command = prompt_complete_line(command);
	// if (asked_for_termination(command))
	// 	exit_shell(EXIT_SUCCESS, e_true);
	// else if (*command == '\0')
	// {
	// 	free(command);
	// 	return (ft_readline(prompt, free_prompt));
	// }
	while (*command == '\0'
			|| e_true == ft_pending_pipe(command))
	{
		command = (ft_strjoin(command, readline('>'),
					e_true, e_true));
	}
	// else if (e_false == ft_quote_occurrence_balanced(command)
	// 		|| e_true == minishell_illegal_chars(command))
	// {
	// 	// TODO
	// }
	// else if (e_true == ft_pending_pipe(command))
	// {
	// 	command = prompt_complete_line(command);
	// 	// TODO
	// }
	if (e_true == here_doc_line(command))
	{
		here_doc_read(command);
	}
	ft_add_history(command);
	if (free_prompt)
		free(prompt);
	return (command);
}

char	*complete_line(char *command)
{
	pid_t	line_cont_prompt;
	int		line_channel[2];
	int		line_size_channel[2];


	pipe(line_channel);
	pipe(line_size_channel);
	line_cont_prompt = fork();
	if (!line_cont_prompt)
	{
		close(line_channel[0]);
		close(line_size_channel[0]);
		line_continuation_prompt(command, line_channel, line_size_channel);
		// TODO
	}
	else
	{
		close(line_channel[1]);
		close(line_size_channel[1]);
		// TODO
	}
}

void	line_continuation_prompt(char *command,
			int line_channel[2], int line_size_channel[2])
{
	t_bool	clean_exit;
	int		command_len;

	command = line_continuation_prompt_rec(command, &clean_exit);
	command_len = ft_strlen(command);	
	write(line_size_channel[1], &command_len, sizeof(command_len));
	write(line_channel[1], command, command_len * sizeof(char));
	free(command);
	if (clean_exit)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

char	*line_continuation_prompt_rec(char *command, t_bool *clean_exit)
{
	char	*continuation;

	continuation = readline(">");
	if (!continuation)
		*clean_exit = e_true;
	else if (*command == '\0')
		*clean_exit = e_false;
	else
	{
		command = ft_strjoin(command, continuation, e_true, e_true);
		if (e_true == ft_pending_pipe(command))
			return (line_continuation_prompt_rec(command, clean_exit));
		else
			*clean_exit = e_true;
	}
	return (command);
}

/**
 * @brief Get the current working directory (not with full path)
 * 
 * @return char* 
 */
char	*get_current_working_directory(void)
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
