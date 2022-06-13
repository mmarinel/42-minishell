/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:31:12 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/19 19:36:16 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	px_exit(t_cmd **last_cmd, int pids);

int	main(int argc, char const *argv[], char *const envp[])
{
	int			pids;
	t_cmd		*last_cmd;

	if (argc-- != 5)
		px_error_handler(0,
			px_strjoin("", "pipex: wrong number of arguments: "), e_true);
	argv++;
	pids = argc - 2;
	px_get_cmds(&last_cmd, argc, argv);
	px_pipex(pids, last_cmd, envp, e_false);
	px_close_pipes(last_cmd);
	px_exit(&last_cmd, pids);
	return (0);
}

void	px_pipex(int pids, t_cmd *current,
			char *const envp[], t_boolean append)
{
	if (pids > 1)
	{
		px_pipex(pids - 1, current->prev, envp, append);
		if (current->is_last)
			px_child(PX_LAST, current, envp, append);
		else
			px_child(PX_MIDDLE, current, envp, e_false);
	}
	else
		px_child(PX_FIRST, current, envp, append);
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
	exit(status);
}
