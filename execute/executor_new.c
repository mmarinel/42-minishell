/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 09:39:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 10:23:02 by mmarinel         ###   ########.fr       */
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












