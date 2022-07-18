/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 10:01:00 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/18 20:28:51 by mmarinel         ###   ########.fr       */
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
	int				cur_line_here_docs;

	signal(SIGINT, SIG_IGN);
	outcome = OK;
	if (here_docs_count(command) == 0)
		return (OK);
	cur_line_here_docs = here_docs_count(command) - 1;
	here_doc_delims = here_doc_take_delimiters(command);
	while (cur_line_here_docs > -1)
	{
		cur_file_name = hdoc_next_file_name();
		outcome = here_doc_read_current(here_doc_delims[(here_docs_count(command) - 1) - cur_line_here_docs],
					cur_file_name);
		cur_line_here_docs--;
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

	// signal(SIGINT, SIG_IGN);
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
	// signal(SIGINT, sig_handler);
	return (outcome);
}

static char	*hdoc_next_file_name(void)
{
	// static size_t	i = 0;//* ci serve statico perche' il tokenizer scannerizza una word alla volta e ad ogni istante deve sapere quanti here_doc ha gia' incontrato per dare il giusto nome al relativo buffer file. Se vogliamo azzerargli il conteggio alla fine della tokenizzazione, dobbiamo chiamare la funzione di scan_in_out con un opportuno opcode.
	size_t	i;
	char			*buffer_file_name;

	i = 0;
	while (e_true)
	{
		buffer_file_name = ft_strjoin(".here_doc-", ft_itoa(i), e_false, e_true);
		if (0 != access(buffer_file_name, R_OK | W_OK))
			break ;
		free(buffer_file_name);
		i++;
	}
	// buffer_file_name = ft_strjoin(".here_doc-", ft_itoa(i), e_false, e_true);
	// i = (i + 1) % g_env.here_docs;
	return (buffer_file_name);
}
