/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:58:05 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 18:02:21 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

void	execute_cmd_builtin(t_simple_command_node simple_cmd)
{
	char	*simple_name;

	cmd_expand(&simple_cmd);
	if (NULL == simple_cmd.cmd_name)
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	else
	{
		simple_name = ft_get_cmd_name(simple_cmd.cmd_name);
		if (0 == ft_strcmp(simple_name, "echo"))
			execute_echo(simple_cmd);
		if (0 == ft_strcmp(simple_name, "cd"))
			execute_cd(simple_cmd);
		if (0 == ft_strcmp(simple_name, "exit"))
			execute_exit(simple_cmd);
		if (0 == ft_strcmp(simple_name, "pwd"))
			execute_pwd(simple_cmd);
		if (0 == ft_strcmp(simple_name, "export"))
			execute_export();
		if (0 == ft_strcmp(simple_name, "unset"))
			execute_unset();
		if (0 == ft_strcmp(simple_name, "env"))
			execute_env(simple_cmd.cmd_args);
		free(simple_name);
	}
}

void	execute_redir_only_statement(t_tree_node *root,
				int in, int out)
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
		{
			perror("minishell at execute_redir_only_statement");
			g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		}
		else
			close(out_fd);
	}
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	if (in || out)
		;
}

void	execute_env_statement(t_env_decl_node env_statement)
{
	_execute_env_statement(env_statement);
}
