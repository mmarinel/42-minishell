/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_statement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:49:38 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 12:45:59 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_statements.h"

static void		spawn_and_wait_command(t_tree_node *root,
					int in, int out);
static void		execute_command_and_exit(t_tree_node *root, int in, int out);
static void		execute_external(t_tree_node *root, int in, int out);

// * end of declarations //


void	execute_simple_statement(t_tree_node *root, int in, int out)
{
	// char	*simple_name;

	// simple_name = ft_get_cmd_name(root->content->simple_cmd.cmd_name);
	// if (0 == ft_strcmp(simple_name, "echo")
	// 	|| 0 == ft_strcmp(simple_name, "cd")
	// 	|| 0 == ft_strcmp(simple_name, "pwd")
	// 	|| 0 == ft_strcmp(simple_name, "export")
	// 	|| 0 == ft_strcmp(simple_name, "unset")
	// 	|| 0 == ft_strcmp(simple_name, "env")
	// 	|| 0 == ft_strcmp(simple_name, "exit")
	// )
	// 	execute_builtin(root->content->simple_cmd, in, out);
	// else
		execute_external(root, in, out);
}

static void	execute_external(t_tree_node *root, int in, int out)
{
	static int	parent_flag = 0;

	parent_flag = (parent_flag + 1) % 2;
	if (parent_flag)
	{
		spawn_and_wait_command(root, in, out);
		parent_flag = 0;
	}
	else
	{
		execute_command_and_exit(root, in, out);
	}
}

static void	spawn_and_wait_command(t_tree_node *root, int in, int out)
{
	t_branch	statement_execution;

	statement_execution.pid = fork();
	if (!statement_execution.pid)
		execute_simple_statement(root, in, out);
	else
	{
		waitpid(statement_execution.pid, &statement_execution.exit_status, 0);
		if (!WIFEXITED(statement_execution.exit_status) || WEXITSTATUS(statement_execution.exit_status))
			g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		else
			g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	}
}

static void	execute_command_and_exit(t_tree_node *root, int in, int out)
{
	if (root->content->content_type == SIMPL_CMD)
		execute_simple_cmd(root, in, out);
	// if (root->content->content_type == ENV_STATEMENT)
	// 	execute_env_statement(root, in, out);
	if (root->content->content_type == REDIR)
		execute_redir_only_statement(root, in, out);
}
