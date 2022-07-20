/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:58:33 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 12:30:29 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec_statements.h"

static void	pipe_execute_branch(t_tree_node *branch, int unused_pipe_side,
				int new_in, int new_out);
static void	inside_tee_wrapper(t_tree_node *root, int in, int out);

// * end of declarations //

void	execute_pipe_statement(t_tree_node *root, int in, int out)
{
	int			new_in_out[2];
	t_branch	left_hand_side;
	t_branch	right_hand_side;

	if (root->is_parse_tree_root == e_true)
		inside_tee_wrapper(root, in, out);
	else
	{
		pipe(new_in_out);
		left_hand_side.pid = fork();
		if (!left_hand_side.pid)
		{
			pipe_execute_branch(root->left, new_in_out[0], in, new_in_out[1]);
		}
		right_hand_side.pid = fork();
		if (!right_hand_side.pid)
		{
			pipe_execute_branch(root->right, new_in_out[1], new_in_out[0], out);
		}
		close(new_in_out[0]);
		close(new_in_out[1]);
		waitpid(left_hand_side.pid, NULL, 0);
		waitpid(right_hand_side.pid, &(right_hand_side.exit_status), 0);
		g_env.last_executed_cmd_exit_status = right_hand_side.exit_status;
	}
	// if (!WIFEXITED(right_hand_side.exit_status) || WEXITSTATUS(right_hand_side.exit_status))
	// 	g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
	// else
	// 	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

static void	inside_tee_wrapper(t_tree_node *root, int in, int out)
{
	static int	count = 0;
	int			new_in_out[2];
	t_branch	right_hand_side;

	pipe(new_in_out);
	right_hand_side.pid = fork();
	if (!right_hand_side.pid)
	{
		count++;
		if (count > 1)
			exit(0);
		pipe_execute_branch(root->right, new_in_out[1], new_in_out[0], out);
	}
	close(new_in_out[0]);
	execute_rec(root->left, in, new_in_out[1]);
	// waitpid(right_hand_side.pid, &(right_hand_side.exit_status), 0);
	// g_env.last_executed_cmd_exit_status = right_hand_side.exit_status;
}

void	execute_and_statement(t_tree_node *root, int in, int out)
{
	execute_rec(root->left, in, out);
	if (g_env.last_executed_cmd_exit_status != EXIT_SUCCESS)
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

static void	pipe_execute_branch(t_tree_node *branch, int unused_pipe_side,
				int new_in, int new_out)
{
	size_t		new_shlvl;

	new_shlvl = atoi(env_handler(BINDING_GET_VALUE, "SHLVL")) + 1;
	env_handler(BINDING_UPDATE,
		get_new_binding("SHLVL", ft_itoa(new_shlvl), e_false)
	);
	// redirector(STDOUT_RESTORE);
	// redirector(STDOUT_2_DUMP);
	close(unused_pipe_side);
	execute_rec(branch, new_in, new_out);
	// redirector(STDOUT_RESTORE);
	exit(g_env.last_executed_cmd_exit_status);
	// if (!WIFEXITED(g_env.last_executed_cmd_exit_status)
	// 	|| WEXITSTATUS(g_env.last_executed_cmd_exit_status))
	// 	exit(EXIT_FAILURE);
	// else
	// 	exit(EXIT_SUCCESS);
}
