/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:58:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:09:04 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_statements.h"

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
