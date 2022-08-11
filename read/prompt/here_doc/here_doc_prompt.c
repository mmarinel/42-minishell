/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:09:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 15:56:44 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static void	hdoc_read_until_complete(int hdoc_fd, char *delimiter);
//* end of static declarations

void	here_doc_prompt(t_hdoc_prompt_behav opcode, char *delimiter,
			char *hdoc_file_name)
{
	int		fd_here_document;

	if (opcode == KILL_HDOC)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, here_doc_prompt_sig_handler);
		unlink(hdoc_file_name);
		fd_here_document = open(hdoc_file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (-1 == fd_here_document)
		{
			perror("minishell at here_doc_prompt");
			exit(EXIT_FAILURE);
		}
		while (e_true)
			hdoc_read_until_complete(fd_here_document, delimiter);
	}
}

static void	hdoc_read_until_complete(int hdoc_fd, char *delimiter)
{
	char	*next_line;

	next_line = readline("heredoc> ");
	if (!next_line
		|| 0 == ft_strcmp(next_line, delimiter))
	{
		close(hdoc_fd);
		ft_free(next_line);
		exit(EXIT_SUCCESS);
	}
	else if (*next_line == '\0')
	{
		free(next_line);
		hdoc_read_until_complete(hdoc_fd, delimiter);
	}
	else
	{
		next_line = expand(ft_strjoin(next_line, "\n", e_true, e_false));
		write(hdoc_fd, next_line, ft_strlen(next_line));
		free(next_line);
	}
}
