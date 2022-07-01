// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/29 10:46:16 by mmarinel          #+#    #+#             */
// /*   Updated: 2022/07/01 09:11:25 by mmarinel         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// # include "executor.h"

// void	execute(t_tree_node *parse_tree)
// {
// 	pid_t	executor;

// 	if (parse_tree == NULL)
// 		return ;
// 	executor = fork();
// 	if (!executor)
// 		execute_rec(parse_tree, STDIN_FILENO, STDOUT_FILENO);
// 	waitpid(executor, &(g_env.last_executed_cmd_exit_status), 0);
// }

// void	execute_rec(t_tree_node *root, int in, int out)
// {
// 	t_branch	left_hand_side;
// 	t_branch	right_hand_side;
// 	int			new_in_out[2];

// 	if (root->content->content_type == SIMPL_CMD
// 		|| root->content->content_type == ENV_STATEMENT
// 		|| root->content->content_type == REDIR)
// 		execute_statement(root, in, out, g_env.export);
// 	else
// 	{
// 		if (root->content->operator_node.operator == e_PIPE)
// 		{
// 			pipe(new_in_out[2]);
// 			left_hand_side.branch = fork();
// 			if (!left_hand_side.branch)
// 			{
// 				close(new_in_out[0]);
// 				execute_rec(root->left, in, new_in_out[1]);
// 			}
// 			right_hand_side.branch = fork();
// 			if (!right_hand_side.branch)
// 			{
// 				close(new_in_out[1]);
// 				execute_rec(root->right, new_in_out[0], out);
// 			}
// 			close(new_in_out[0]);
// 			close(new_in_out[1]);
// 			waitpid(left_hand_side.branch, &(left_hand_side.exit_status), 0);
// 			waitpid(right_hand_side.branch, &(right_hand_side.exit_status), 0);
// 			if ((!WIFEXITED(left_hand_side.exit_status) || WEXITSTATUS(left_hand_side.exit_status))
// 				|| (!WIFEXITED(right_hand_side.exit_status) || WEXITSTATUS(right_hand_side.exit_status)))
// 				exit(EXIT_FAILURE);
// 			exit(EXIT_SUCCESS);
// 		}
// 		if (root->content->operator_node.operator == e_AND)
// 		{
// 			pipe(new_in_out[2]);
// 			left_hand_side.branch = fork();
// 			if (!left_hand_side.branch)
// 			{
// 				close(new_in_out[0]);
// 				execute_rec(root->left, in, new_in_out[1]);
// 			}
// 			waitpid(left_hand_side.branch, &(left_hand_side.exit_status), 0);
// 			if ((!WIFEXITED(left_hand_side.exit_status) || WEXITSTATUS(left_hand_side.exit_status)))
// 			{
// 				close(new_in_out[0]);
// 				close(new_in_out[1]);
// 				exit(EXIT_FAILURE);
// 			}
// 			right_hand_side.branch = fork();
// 			if (!right_hand_side.branch)
// 			{
// 				close(new_in_out[1]);
// 				execute_rec(root->right, new_in_out[0], out);
// 			}
// 			waitpid(right_hand_side.branch, &(right_hand_side.exit_status), 0);
// 			close(new_in_out[0]);
// 			close(new_in_out[1]);
// 			if ((!WIFEXITED(right_hand_side.exit_status) || WEXITSTATUS(right_hand_side.exit_status)))
// 				exit(EXIT_FAILURE);
// 			exit(EXIT_SUCCESS);
// 		}
// 		if (root->content->operator_node.operator == e_OR)
// 		{
// 			pipe(new_in_out[2]);
// 			left_hand_side.branch = fork();
// 			if (!left_hand_side.branch)
// 			{
// 				close(new_in_out[0]);
// 				execute_rec(root->left, in, new_in_out[1]);
// 			}
// 			waitpid(left_hand_side.branch, &(left_hand_side.exit_status), 0);
// 			if (WIFEXITED(left_hand_side.exit_status) && !WEXITSTATUS(left_hand_side.exit_status))
// 			{
// 				close(new_in_out[0]);
// 				close(new_in_out[1]);
// 				exit(EXIT_SUCCESS);
// 			}
// 			right_hand_side.branch = fork();
// 			if (!right_hand_side.branch)
// 			{
// 				close(new_in_out[1]);
// 				execute_rec(root->right, new_in_out[0], out);
// 			}
// 			waitpid(right_hand_side.branch, &(right_hand_side.exit_status), 0);
// 			close(new_in_out[0]);
// 			close(new_in_out[1]);
// 			if ((!WIFEXITED(right_hand_side.exit_status) || WEXITSTATUS(right_hand_side.exit_status)))
// 				exit(EXIT_FAILURE);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// }

// void	exit_execution(t_branch left_hand_side, t_branch right_hand_side, t_operator operator, int new_in_out[2])
// {
// 	close(new_in_out[0]);
// 	close(new_in_out[1]);
// 	if (operator != e_PIPE)
// 		exit(EXIT_SUCCESS);
// 	else
// 	{
// 		waitpid(left_hand_side.branch, &(left_hand_side.exit_status), 0);
// 		waitpid(right_hand_side.branch, &(right_hand_side.exit_status), 0);
// 		if (
// 			(
// 				!WIFEXITED(left_hand_side.exit_status)
// 				|| WEXITSTATUS(left_hand_side.exit_status)
// 			)
// 			||
// 			(
// 				!WIFEXITED(right_hand_side.exit_status)
// 				|| WEXITSTATUS(right_hand_side.exit_status)
// 			)
// 		)
// 			exit(EXIT_FAILURE);
// 		exit(EXIT_SUCCESS);
// 	}
// }

// t_branch	execute_branch(t_tree_node *new_root, t_operator operator,int old_in_out, int new_in_out[2])
// {
// 	t_branch	branch_handle;

// 	branch_handle.branch = fork();
// 	if (!branch_handle.branch)
// 	{
// 		// TODO .....
// 	}
// 	else
// 	{
// 		// TODO ......
// 	}
// }











