/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:01:00 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/08 15:06:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

static t_status		here_doc_read_current(char *delimiter, char *handle_name);
static char			*hdoc_next_file_name(void);

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
			here_doc_delims[here_docs_count(command) - cur_hdoc_cont_id - 1],
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

static t_status	here_doc_read_current(char *delimiter, char *hdoc_file_name)
{
	t_status	outcome;
	pid_t		hdoc_prompt_pid;
	int			hdoc_prompt_exit_status;

	hdoc_prompt_pid = fork();
	if (!hdoc_prompt_pid)
	{
		here_doc_prompt(CONTINUE, delimiter, hdoc_file_name);
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
