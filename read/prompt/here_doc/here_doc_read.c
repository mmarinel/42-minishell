/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:01:00 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 16:41:02 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static t_status	here_doc_read_current(char **delimiter, char *hdoc_file_name);
static char			*hdoc_next_file_name(void);
static void			expand_delimiter_take_quote(char **delimiter,
						char *delimiter_enclosing_quote);
//* end of static declarations //

t_status	here_doc_read(char *command)
{
	t_status		outcome;
	char			*cur_file_name;
	char			**here_doc_delims;
	int				cur_hdoc_cont_id;

	if (here_docs_count(command) == 0)
		return (OK);
	outcome = OK;
	signal(SIGINT, sig_ign);
	cur_hdoc_cont_id = here_docs_count(command) - 1;//* n - 1
	here_doc_delims = here_doc_take_delimiters(command);
	while (cur_hdoc_cont_id > -1)
	{
		cur_file_name = hdoc_next_file_name();
		outcome = here_doc_read_current(
			&here_doc_delims[here_docs_count(command) - cur_hdoc_cont_id - 1],
			cur_file_name
		);
		cur_hdoc_cont_id--;
		free(cur_file_name);
		if (outcome == ERROR)
			break ;
	}
	ft_splitclear(here_doc_delims);
	return (outcome);
}

static t_status	here_doc_read_current(char **delimiter, char *hdoc_file_name)
{
	t_status	outcome;
	pid_t		hdoc_prompt_pid;
	int			hdoc_prompt_exit_status;
	char		delimiter_enclosing_quote;

	hdoc_prompt_pid = fork();
	if (!hdoc_prompt_pid)
	{
		expand_delimiter_take_quote(delimiter, &delimiter_enclosing_quote);
		here_doc_prompt(CONTINUE, delimiter_enclosing_quote,
			*delimiter, hdoc_file_name);
	}
	waitpid(hdoc_prompt_pid, &hdoc_prompt_exit_status, 0);
	if (!WIFEXITED(hdoc_prompt_exit_status)
		|| WEXITSTATUS(hdoc_prompt_exit_status))
		outcome = ERROR;
	else
		outcome = OK;
	return (outcome);
}

static char	*hdoc_next_file_name(void)
{
	char			*buffer_file_name;
	size_t			i;

	i = 0;
	while (e_true)
	{
		buffer_file_name = ft_strjoin(".here_doc-", ft_itoa(i), e_false, e_true);
		if (0 != access(buffer_file_name, R_OK | W_OK))
			break ;
		free(buffer_file_name);
		i++;
	}
	return (buffer_file_name);
}

static void	expand_delimiter_take_quote(char **delimiter,
				char *delimiter_enclosing_quote)
{
	if ((*delimiter)
		&& ((*delimiter)[0] == '\'' || (*delimiter)[0] == '"'))
		*delimiter_enclosing_quote = (*delimiter)[0];
	else
		*delimiter_enclosing_quote = 0;
	{
		if (0 == *delimiter_enclosing_quote)
			(*delimiter) = expand((*delimiter));
		else
			ft_str_replace(
				delimiter,
				ft_strcpy(NULL, *delimiter + 1, ft_strlen(*delimiter) - 2)
			);
	}
}
