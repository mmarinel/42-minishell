/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:09:03 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/17 12:35:39 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt_utils.h"

static void	hdoc_read_until_complete(char **continuation,
			int line_channel[2], int line_size_channel[2]);

void	here_doc_prompt(t_prompt_behav opcode, char *delimiter, int	hdoc_fd)
{
	int		fd_here_document;
	char	*next_line;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, here_doc_prompt_sig_handler);
	unlink(handle_name);
	fd_here_document = open(handle_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (-1 == fd_here_document)
	{
		perror("minishell at here_doc_prompt");
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
