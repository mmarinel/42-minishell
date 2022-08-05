/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_statement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:49:38 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/05 20:23:15 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_statements.h"

static void		spawn_and_wait_command(t_tree_node *root,
					int in, int out);
static void		execute_command_and_exit(t_tree_node *root, int in, int out);
static void		execute_external(t_tree_node *root, int in, int out);

static void		execute_builtin(t_tree_node *root, int in, int out);

// * end of declarations //

void	execute_simple_statement(t_tree_node *root, int in, int out)
{
	if (e_true == is_builtin_command(root))
		execute_builtin(root, in, out);
	else
		execute_external(root, in, out);
}

static void	execute_builtin(t_tree_node *root, int in, int out)
{
	int			stdin_clone;
	int			stdout_clone;

	stdin_clone = dup(STDIN_FILENO);
	stdout_clone = dup(STDOUT_FILENO);
	if (ERROR == builtin_handle_redirs(root->content->in_redir,
			in, STDIN_FILENO, e_true))
	{
		perror("minishell: ");
		g_env.last_executed_cmd_exit_status = 1;
	}
	else
	{
		builtin_handle_redirs(root->content->out_redir,
			out, STDOUT_FILENO, e_false);
		if (root->content->content_type == ENV_STATEMENT)
			execute_env_statement(root->content->env_decl);
		else if (root->content->content_type == REDIR)
			execute_redir_only_statement(root, in, out);
		else
			execute_cmd_builtin(root->content->simple_cmd);
	}
	dup2(stdin_clone, STDIN_FILENO);
	dup2(stdout_clone, STDOUT_FILENO);
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
		// close(in);
		// close(out);
	}
}

static void	spawn_and_wait_command(t_tree_node *root, int in, int out)
{
	t_branch	statement_execution;

	int	cur_stdout_backup = dup(STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	statement_execution.pid = fork();
	if (statement_execution.pid == 0)
		execute_simple_statement(root, in, out);
	else
	{
		waitpid(statement_execution.pid, &(statement_execution.exit_status), 0);
		dup2(cur_stdout_backup, STDOUT_FILENO);
		close(cur_stdout_backup);
		signal(SIGINT, sig_handler);
		g_env.last_executed_cmd_exit_status
			= WEXITSTATUS(statement_execution.exit_status);
	}
}

static void	execute_command_and_exit(t_tree_node *root, int in, int out)
{
	if (root->content->content_type == SIMPL_CMD)
		execute_external_simple_cmd(root, in, out);
	// if (root->content->content_type == REDIR)
	// 	execute_redir_only_statement(root, in, out);
}
