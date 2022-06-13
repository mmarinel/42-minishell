/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:29:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/20 10:04:51 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	px_here_doc(char const *argv[]);
static void	px_exit(t_cmd **last_cmd, int pids);

int	main(int argc, char const *argv[], char *const envp[])
{
	int			pids;
	t_cmd		*last_cmd;
	t_boolean	append;

	if (argc-- < 5)
		px_error_handler(0,
			px_strjoin("", "pipex: wrong number of arguments: "), e_true);
	argv++;
	append = e_false;
	if (px_strcmp((char *) argv[0], "here_doc"))
	{
		px_here_doc(++argv);
		append = e_true;
		argc--;
	}
	pids = argc - 2;
	px_get_cmds(&last_cmd, argc, argv);
	px_pipex_bonus(pids, last_cmd, envp, append);
	px_close_pipes(last_cmd);
	px_exit(&last_cmd, pids);
	return (0);
}

void	px_pipex_bonus(int pids, t_cmd *current,
			char *const envp[], t_boolean append)
{
	if (pids > 1)
	{
		px_pipex_bonus(pids - 1, current->prev, envp, append);
		if (current->is_last)
			px_child(PX_LAST, current, envp, append);
		else
			px_child(PX_MIDDLE, current, envp, e_false);
	}
	else
		px_child(PX_FIRST, current, envp, append);
}

static void	px_here_doc(char const *argv[])
{
	int		fd;
	char	*next_line;
	char	*here_doc;

	here_doc = ".here_doc";
	fd = open(here_doc, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (-1 == fd)
		px_error_handler(0, NULL, e_false);
	next_line = get_next_line(STDIN_FILENO);
	while (!px_strcmp((char *) argv[0], next_line))
	{
		write(fd, next_line, ft_strlen(next_line));
		free(next_line);
		next_line = get_next_line(STDIN_FILENO);
	}
	free(next_line);
	close(fd);
}

static void	px_exit(t_cmd **last_cmd, int pids)
{
	int	status;
	int	old_status;

	status = 0;
	old_status = 0;
	while (pids--)
	{
		wait(&status);
		status = (old_status || (!WIFEXITED(status) || WEXITSTATUS(status)));
		old_status = status;
	}
	px_lstclear(last_cmd, NULL);
	unlink(".here_doc");
	exit(status);
}
