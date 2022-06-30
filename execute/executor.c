// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/29 10:46:16 by mmarinel          #+#    #+#             */
// /*   Updated: 2022/06/30 10:51:52 by mmarinel         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// # include "executor.h"

// void	execute(t_tree_node *parse_tree, char *const envp[])
// {
// 	pid_t	executor;

// 	if (parse_tree == NULL)
// 		return ;
// 	executor = fork();
// 	if (!executor)
// 		execute_rec(parse_tree, STDIN_FILENO, STDOUT_FILENO, envp);
// 	waitpid(executor, &(g_env.last_executed_cmd_status), 0);
// }

// void	execute_rec(t_tree_node *root, int in, int out, char *const envp[])
// {
// 	t_branch	left_hand_side;
// 	t_branch	right_hand_side;
// 	int			new_in_out[2];

// 	if (root->content->content_type == SIMPL_CMD
// 		|| root->content->content_type == ENV_STATEMENT
// 		|| root->content->content_type == REDIR)
// 		execute_statement(root, in, out, envp);
// 	else
// 	{
// 		if (root->content->operator_node.operator == e_PIPE)
// 		{
// 			pipe(new_in_out[2]);
// 			left_hand_side.branch = fork();
// 			if (!left_hand_side.branch)
// 				return (execute_rec(root->left, in, new_in_out[1], envp));
// 			right_hand_side.branch = fork();
// 			if (!right_hand_side.branch)
// 				return (execute_rec(root->right, new_in_out[0], out, envp));
// 			return ;
// 		}
// 		if (root->content->operator_node.operator == e_OR)
// 		{
// 			left_hand_side.branch = fork();
// 			if (!left_hand_side.branch)
// 				return (execute_rec(root->left, in, out, envp));
// 			waitpid(left_hand_side.branch, &(left_hand_side.exit_status), 0);
// 			if (left_hand_side.exit_status == EXIT_SUCCESS)
// 				return ;
// 			right_hand_side.branch = fork();
// 			if (!right_hand_side.branch)
// 				return (execute_rec(root->right, in, out, envp));
// 			waitpid(right_hand_side.branch, &(right_hand_side.exit_status), 0);
// 			return ;
// 		}
// 		if (root->content->operator_node.operator == e_AND)
// 		{
// 			left_hand_side.branch = fork();
// 			if (!left_hand_side.branch)
// 				return (execute_rec(root->left, in, out, envp));
// 			waitpid(left_hand_side.branch, &(left_hand_side.exit_status), 0);
// 			if (left_hand_side.exit_status != EXIT_SUCCESS)
// 				return ;
// 			right_hand_side.branch = fork();
// 			if (!right_hand_side.branch)
// 				return (execute_rec(root->right, in, out, envp));
// 			waitpid(right_hand_side.branch, &(right_hand_side.exit_status), 0);
// 			return ;
// 		}
// 		// else
// 		// {
// 		// 	new_in_out[0] = in;
// 		// 	new_in_out[1] = out;
// 		// }
// 		// left_hand_side = fork();
// 		// if (!left_hand_side)
// 		// {
// 		// 	// TODO
// 		// }
// 		// right_hand_side = fork();
// 		// if (!right_hand_side)
// 		// {
// 		// 	// TODO
// 		// }
// 	}
// }
