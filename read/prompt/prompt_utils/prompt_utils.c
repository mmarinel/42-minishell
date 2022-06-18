/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:00:15 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/18 19:19:49 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

t_bool	here_doc_line(char *command)
{
	return (here_doc_take_delimiter(command) != NULL);
}

void	here_doc_read(char *delimiter)
{
	int		fd_here_document;
	char	*next_line;
	char	*here_doc;
	int		delimiter_len;

	here_doc = ".here_doc";
	delimiter_len = ft_strlen(delimiter);
	fd_here_document = open(here_doc, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (-1 == fd_here_document)
		exit_shell(EXIT_FAILURE, e_false);
	while (e_true)
	{
		next_line = get_next_line(STDIN_FILENO, 1);
		write(fd_here_document, next_line, ft_strlen(next_line));
		// printf("delimiter is %s and len is %d\n", delimiter, delimiter_len);
		if (!ft_strncmp(delimiter, next_line, delimiter_len))
			break ;
		else
			free(next_line);
	}
	free(next_line);
	close(fd_here_document);
}

char	*here_doc_take_delimiter(char *command)
{
	char	*start;

	start = take_substr(command, "<<");
	printf("here_doc: %s\n", start);
	if (!start)
		return (NULL);
	start += 2;
	while (ft_isspace(*start))
		start++;
	return (take_next_word(command));
}
