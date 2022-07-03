/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:15:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:18:26 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

void	execute_simple_cmd(t_tree_node *root, int in, int out)
{
	char	*cmd_simple_name;
	char	*cmd_full_path;
	char	**args;

	args = NULL;
	executor_handle_redirs(root->content->in_redir,
		in, STDIN_FILENO, e_true);
	executor_handle_redirs(root->content->out_redir,
		out, STDOUT_FILENO, e_false);
	cmd_simple_name = get_cmd_simple_name(root->content->simple_cmd.cmd_name);
	cmd_full_path = get_cmd_full_path(root->content->simple_cmd.cmd_name);
	args = ft_split(
			ft_strjoin(
				cmd_simple_name,
				root->content->simple_cmd.cmd_args, e_true, e_false),
			' ');
	if (!cmd_full_path)
		command_not_found_failure(root, cmd_full_path, cmd_simple_name, args);
	if (-1 == execve(cmd_full_path, args, g_env.env))
		command_execution_failure(root, cmd_full_path, cmd_simple_name, args);
}

void	execute_redir_only_statement(t_tree_node *root, int in, int out)
{
	int	out_fd;

	out_fd = 0;
	if (root->content->out_redir.file_name)
	{
		if (root->content->out_redir.append_mode == e_true)
			out_fd = open(root->content->out_redir.file_name,
						O_CREAT | O_APPEND | O_WRONLY, 0777);
		else
			out_fd = open(root->content->out_redir.file_name,
						O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (out_fd == -1)
			perror("minishell at execute_redir_only_statement: ");
		else
			close(out_fd);
	}
}

static void	executor_handle_redirs(t_redirection redir, int cur_in_out,
			int	std_in_out, t_bool redirect_input)
{
	if (redir.file_name)
	{
		if (cur_in_out != std_in_out) // * this means we are inside a PIPE but have to use the explicit redirection (>, <. etc.)
		{
			close(cur_in_out);
		}
		{
			if (redirect_input == e_true)
				cur_in_out = open(redir.file_name, O_RDONLY);
			else
			{
				if (redir.append_mode == e_true)
					cur_in_out = open(redir.file_name,
								O_CREAT | O_APPEND | O_WRONLY, 0777);
				else
					cur_in_out = open(redir.file_name,
								O_CREAT | O_TRUNC | O_WRONLY, 0777);
			}
		}
	}
	if (cur_in_out != std_in_out)
	{
		dup2(cur_in_out, std_in_out);
		close(cur_in_out);
	}
}
