/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:46:54 by mmarinel          #+#    #+#             */
/*   Updated: 2022/03/20 10:01:32 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_children.h"

static void	px_child_born(int mode, t_cmd *current,
				char *const envp[], t_boolean append);

pid_t	px_child(int mode, t_cmd *current, char *const envp[], t_boolean append)
{
	pid_t	child;

	child = fork();
	if (!child)
		px_child_born(mode, current, envp, append);
	else if (child < 0)
		px_error_handler(0, NULL, e_false);
	return (child);
}

static void	px_child_born(int mode, t_cmd *current,
				char *const envp[], t_boolean append)
{
	char	*cmd_name;
	char	*cmd_full_path;
	char	**arg_list;

	px_redirections(mode, current, append);
	px_close_pipes(current);
	cmd_name = ft_get_cmd_name(current->cmd);
	cmd_full_path = ft_return_path(cmd_name, envp);
	if (!cmd_full_path)
		px_error_handler(0,
			px_strjoin("zsh: command not found: ", current->cmd), e_true);
	arg_list = px_split(current->cmd, ' ');
	if (arg_list)
		arg_list[0] = px_str_replace(&arg_list[0], &cmd_name, e_true);
	if (-1 == execve(cmd_full_path, arg_list, envp))
	{
		px_free(cmd_full_path);
		px_splitclear(arg_list);
		px_error_handler(0, NULL, e_false);
	}
}

void	px_close_pipes(t_cmd *current)
{
	while (current && current->prev)
		current = current->prev;
	while (current && !(current->is_last))
	{
		close(current->outpipe[1]);
		close(current->outpipe[0]);
		current = current->next;
	}
}
