/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 09:39:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 11:37:03 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute_rec(t_tree_node *root, int in, int out)
{
	if (root->launch_subshell == e_true)
		execute_subshell(root, in, out);
	else
		execute_in_shell(root, in, out);
}

void	execute_subshell(t_tree_node *root, int in, int out)
{
	int	subshell_pid;
	int	subshell_exit_status;

	root->launch_subshell = e_false;
	subshell_pid = fork();
	if (!subshell_pid)
	{
		execute_rec(root, in, out);
		if (!WIFEXITED(g_env.last_executed_cmd_exit_status)
			|| WEXITSTATUS(g_env.last_executed_cmd_exit_status))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	waitpid(subshell_pid, &subshell_exit_status, 0);
	if (!WIFEXITED(subshell_exit_status) || WEXITSTATUS(subshell_exit_status))
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	else
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

void	execute_in_shell(t_tree_node *root, int in, int out)
{
	if (root->content->content_type == SIMPL_CMD
		|| root->content->content_type == ENV_STATEMENT
		|| root->content->content_type == REDIR)
		execute_simple_statement(root, in, out);
	else if (root->content->content_type == OPERATOR
			&& root->content->operator_node.operator == e_PIPE)
		execute_pipe_statement(root, in, out);
	else if (root->content->content_type == e_AND
			&& root->content->operator_node.operator == e_AND)
		execute_and_statement(root, in, out);
	else if (root->content->content_type == e_OR
			&& root->content->operator_node.operator == e_OR)
		execute_or_statement(root, in, out);
	else
		exit(EXIT_FAILURE);
}

void	execute_simple_statement(t_tree_node *root, int in, int out)
{
	static int	parent_flag = 0;
	t_branch	statement_execution;

	parent_flag = (parent_flag + 1) % 2;
	if (parent_flag)
	{
		statement_execution.pid = fork();
		if (!statement_execution.pid)
			execute_simple_statement(root, in, out);
		waitpid(statement_execution.pid, &statement_execution.exit_status, 0);
		if (!WIFEXITED(statement_execution.exit_status) || WEXITSTATUS(statement_execution.exit_status))
			g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		else
			g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
	}
	else
	{
		if (root->content->content_type == SIMPL_CMD)
			execute_simple_cmd(root, in, out);
		if (root->content->content_type == ENV_STATEMENT)
			execute_env_statement(root, in, out);
		if (root->content->content_type == REDIR)
			execute_redir_only_statement(root, in, out);
	}
}

void	execute_simple_cmd(t_tree_node *root, int in, int out)
{
	char	*cmd_simple_name;
	char	*cmd_full_path;
	char	**args;

	// * in
	if (root->content->infile)
	{
		if (in != STDIN_FILENO)
			close(in);
		in = open(root->content->infile, O_RDONLY);
	}
	if (in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	// * out
	if (root->content->outfile)
	{
		if (out != STDOUT_FILENO)
			close(out);
		out = open(root->content->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0777); // ! gestire caso APPEND !!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	if (out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	cmd_simple_name = get_cmd_simple_name(root->content->simple_cmd.cmd_name);
	cmd_full_path = get_cmd_full_path(root->content->simple_cmd.cmd_name);
	if (!cmd_full_path)
		px_error_handler(0,
			px_strjoin("minishell: command not found: ", root->content->simple_cmd.cmd_name), e_true);
	args = ft_split(ft_strjoin(cmd_simple_name, root->content->simple_cmd.cmd_args, e_true, e_false), ' ');
	if (-1 == execve(cmd_full_path, args, g_env.env))
	{
		ft_free(cmd_full_path);
		ft_splitclear(args);
		px_error_handler(0, NULL, e_false); // ! EXIT_FAILURE
	}
}

void	execute_pipe_statement(t_tree_node *root, int in, int out)
{
	int			new_in_out[2];
	t_branch	left_hand_side;
	t_branch	right_hand_side;

	pipe(new_in_out);
	left_hand_side.pid = fork();
	if (!left_hand_side.pid)
	{
		close(new_in_out[0]);
		execute_rec(root->left, in, new_in_out[1]);
		if (!WIFEXITED(g_env.last_executed_cmd_exit_status)
			|| WEXITSTATUS(g_env.last_executed_cmd_exit_status))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	right_hand_side.pid = fork();
	if (!right_hand_side.pid)
	{
		close(new_in_out[1]);
		execute_rec(root->right, new_in_out[0], out);
		if (!WIFEXITED(g_env.last_executed_cmd_exit_status)
			|| WEXITSTATUS(g_env.last_executed_cmd_exit_status))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	waitpid(left_hand_side.pid, NULL, 0);
	waitpid(right_hand_side.pid, &(right_hand_side.exit_status), 0);
	if (!WIFEXITED(right_hand_side.exit_status) || WEXITSTATUS(right_hand_side.exit_status))
		g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	else
		g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

void	execute_and_statement(t_tree_node *root, int in, int out)
{
	execute_rec(root->left, in, out);
	if (g_env.last_executed_cmd_exit_status == EXIT_FAILURE)
		return ;
	execute_rec(root->right, in, out);
}

void	execute_or_statement(t_tree_node *root, int in, int out)
{
	execute_rec(root->left, in, out);
	if (g_env.last_executed_cmd_exit_status == EXIT_SUCCESS)
		return ;
	execute_rec(root->right, in, out);
}












