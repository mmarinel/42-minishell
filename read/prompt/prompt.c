/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:34:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 13:18:14 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char		*get_decorated_cwd(char *cwd);

static t_status	complete_line(char **initial_command_ref,
					char *initial_command);
static t_status	read_completed_line(char **command,
					pid_t line_completion_prompt_pid,
					int line_channel[], int line_size_channel[]);
// * end of static declarations //

// * alert 1
// ! readline library function always takes terminating '\n' off,
// ! so a new line is actually EOF (\0)
/**
 * @brief This function tries to read a line until a non-empty/non-pending
 * one is entered or ctr + D is hit.
 * n.b.: A string containing only whitespaces is not considered empty
 * for this function.
 * Here_Doc is managed too.
 * 
 * @param prompt the prompt to be displayed with the readline library function.
 * @return char* the next line read
 * (except here_doc content which is put in a hidden file for later use)
 */
char	*ft_read_command(char *main_prompt)
{
	char		*command;
	t_status	prompt_status;

	command = ft_readline(main_prompt);
	if (!command)
	{
		exit_shell(g_env.last_executed_cmd_exit_status);
	}
	prompt_status = complete_line(&command, command);
	ft_add_history(command);
	if (prompt_status == ERROR)
	{
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		free(command);
		command = NULL;
	}
	free(main_prompt);
	return (command);
}

static t_status	complete_line(char **initial_command_ref,
					char *initial_command)
{
	t_status	outcome;
	pid_t		line_cont_prompt_pid;
	int			line_channel[2];
	int			line_size_channel[2];

	pipe(line_channel);
	pipe(line_size_channel);
	line_cont_prompt_pid = fork();
	if (!line_cont_prompt_pid)
	{
		line_continuation_prompt(COMPLETE_LINE, initial_command,
			line_channel, line_size_channel);
	}
	else
	{
		signal(SIGINT, sig_ign);
		outcome = read_completed_line(initial_command_ref,
				line_cont_prompt_pid,
				line_channel, line_size_channel);
		signal(SIGINT, sig_handler);
	}
	close_pipe(line_channel);
	close_pipe(line_size_channel);
	return (outcome);
}

static t_status	read_completed_line(char **command,
					pid_t line_completion_prompt_pid,
					int line_channel[], int line_size_channel[])
{
	t_status	outcome;
	char		*completed;
	size_t		completion_len;
	int			line_completion_prompt_exit_status;

	close(line_channel[1]);
	close(line_size_channel[1]);
	waitpid(line_completion_prompt_pid, &line_completion_prompt_exit_status, 0);
	if (!WIFEXITED(line_completion_prompt_exit_status)
		|| WEXITSTATUS(line_completion_prompt_exit_status))
		outcome = ERROR;
	else
		outcome = OK;
	read(line_size_channel[0], &completion_len, sizeof(completion_len));
	if (completion_len)
	{
		completed = (char *) malloc((completion_len + 1) * sizeof(char));
		read(line_channel[0], completed, completion_len * sizeof(char));
		completed[completion_len] = '\0';
		ft_str_replace(command, completed);
	}
	return (outcome);
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
	if (0 == ft_strcmp(abs_path, env_handler(BINDING_GET_VALUE, "HOME")))
		return (ft_strjoin(
				ft_itoa(g_env.last_executed_cmd_exit_status),
				" in 📁:-" CYAN " ~ " RESET,
				e_true, e_false)
		);
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
	char	*color;

	if (g_env.last_executed_cmd_exit_status == EXIT_SUCCESS)
		color = GREEN;
	else
		color = RED;
	return (
		ft_strjoin(
			ft_itoa(g_env.last_executed_cmd_exit_status),
			ft_strjoin
			(
				" in 📁:-",
				ft_strjoin
				(
					ft_strjoin(color, cwd, e_false, e_false),
					": " RESET,
					e_true,
					e_false
				),
				e_false,
				e_true
			),
			e_true, e_true
		)
	);
}
