/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:01:00 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 17:18:36 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_utils.h"

static void		here_doc_read_current(char *delimiter, char *handle_name);
static size_t	here_docs_count(char *command);
static char		**here_doc_take_delimiters(char *command);
static void		here_doc_prompt(char *delimiter, char *handle_name);

t_bool	here_doc_line(char *command)
{
	return (here_docs_count(command) > 0);
}

void	here_doc_read(char *command)
{
	char			*cur_file_name;
	char			**here_doc_delims;
	size_t			here_docs;
	static size_t	i = 0;

	here_docs = here_docs_count(command);
	here_doc_delims =  here_doc_take_delimiters(command);
	// i = 0;
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
	// printf("last delim: %s\n", here_doc_delims[1]);
	ft_splitclear(here_doc_delims);
}

static void	here_doc_read_current(char *delimiter, char *handle_name)
{
	pid_t	hdoc_prompt_pid;
	int		hdoc_prompt_exit_status;
	// int		fd_here_document;

	// printf("here_doc is %s\n", handle_name);
	// fd_here_document = open(handle_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	// if (-1 == fd_here_document)
	// 	exit_shell(EXIT_FAILURE, e_false);
	hdoc_prompt_pid = fork();
	if (!hdoc_prompt_pid)
	{
		here_doc_prompt(delimiter, handle_name);
	}
	// close(fd_here_document);
	waitpid(hdoc_prompt_pid, &hdoc_prompt_exit_status, 0);
	if (!WIFEXITED(hdoc_prompt_exit_status) || WEXITSTATUS(hdoc_prompt_exit_status))
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	else
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

static void	here_doc_prompt(char *delimiter, char *handle_name)
{
	int		fd_here_document;
	char	*next_line;

	signal(SIGINT, SIG_IGN);
	unlink(handle_name);
	fd_here_document = open(handle_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (-1 == fd_here_document)
	{
		perror("minishell at here_doc_prompt: ");
		exit(EXIT_FAILURE);
	}
	while (e_true)
	{
		next_line = readline("heredoc> ");
		// printf("delimiter is %s\n", delimiter);
		if (!next_line
			|| 0 == ft_strcmp(next_line, delimiter))
		{
			close(fd_here_document);
			ft_free(next_line);
			exit(EXIT_SUCCESS);
		}
		else if (*next_line == '\0')
		{
			write(fd_here_document, "", 0);
			close(fd_here_document);
			free(next_line);
			exit(EXIT_FAILURE);
		}
		else
		{
			next_line = ft_strjoin(next_line, "\n", e_true, e_false);
			write(fd_here_document, next_line, ft_strlen(next_line));
			free(next_line);
		}
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

