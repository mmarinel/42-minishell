/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:01:00 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 12:42:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_utils.h"

static void		here_doc_read_current(char *delimiter, char *handle_name);
static size_t	here_docs_count(char *command);
static char		**here_doc_take_delimiters(char *command);
static void		here_doc_prompt(char *delimiter, char *handle_name);

//* end of static declarations //


t_bool	here_doc_line(char *command)
{
	if (!command)
		return (e_false);
	return (here_docs_count(command) > 0);
}

t_status	here_doc_read(char **command)
{
	char			*cur_file_name;
	char			**here_doc_delims;
	size_t			here_docs;
	static size_t	i = 0;

	here_docs = here_docs_count(command);
	here_doc_delims =  here_doc_take_delimiters(command);
	while (here_docs--)
	{
		cur_file_name = ft_strjoin(".here_doc-", ft_itoa(i), e_false, e_true);
		here_doc_read_current(here_doc_delims[here_docs], cur_file_name);
		free(cur_file_name);
		if (g_env.last_executed_cmd_exit_status == EXIT_FAILURE)
			break ;
		else
			i++;
	}
	ft_splitclear(here_doc_delims);
}

static t_status	here_doc_read_current(char *delimiter, char *hdoc_file_name)
{
	pid_t	hdoc_prompt_pid;
	int		hdoc_prompt_exit_status;
	int		line_channel[2];
	int		line_size_channel[2];

	pipe(line_channel);
	pipe(line_size_channel);
	hdoc_prompt_pid = fork();
	if (!hdoc_prompt_pid)
	{
		here_doc_prompt(delimiter, hdoc_file_name);
	}
	waitpid(hdoc_prompt_pid, &hdoc_prompt_exit_status, 0);
	if (!WIFEXITED(hdoc_prompt_exit_status) || WEXITSTATUS(hdoc_prompt_exit_status))
	{
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	else
	{
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
		return (OK);
	}
}

static size_t	here_docs_count(char *command)
{
	size_t	i;
	size_t	here_docs;

	here_docs = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] == '<')
			return (0);
		if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] != '<')
			here_docs++;
		i++;
	}
	return (here_docs);
}

static char	**here_doc_take_delimiters(char *command)
{
	size_t	i;
	size_t	j;
	size_t	here_docs;
	char	**here_docs_file_names;

	here_docs = here_docs_count(command);
	if (here_docs == 0)
		return (NULL);
	here_docs_file_names = (char **) malloc((here_docs + 1) * sizeof(char *));
	here_docs_file_names[here_docs] = NULL;
	j = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '<' && command[i + 1] == '<')
		{
			i += 2;
			while (e_true == ft_isspace(command[i]))
				i++;
			here_docs_file_names[j] = take_next_word(command + i);
			j++;
		}
		else
			i++;
	}
	return (here_docs_file_names);
}

