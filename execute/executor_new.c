/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 09:39:10 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/01 15:27:17 by mmarinel         ###   ########.fr       */
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
		if (in_fd == -1)
			perror("minishell at execute_redir_only_statement: ");
		else
			close(out_fd);
	}
}

void	execute_env_statement(t_tree_node *root, int in, int out)
{
	t_bindings	*cur_binding;

	cur_binding = root->content->env_decl.bindings;
	while (cur_binding)
	{
		if (root->content->env_decl.set)
		{
			add_new_binding(&(g_env.export), binding, e_true);
			add_new_binding(&(g_env.env), binding, e_true);
		}
		else
		{
			remove_binding(&(g_env.export), binding, e_true);
			remove_binding(&(g_env.env), binding, e_true);
		}
		cur_binding = cur_binding->next;
	}
}

void	executor_handle_redirs(t_redirection redir, int cur_in_out,
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

void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	printf("minishell: command not found ->" RED "%s" RESET,
		root->content->simple_cmd.cmd_name);
	free(cmd_full_path);
	free(cmd_simple_name);
	ft_splitclear(args);
	exit_command_subshell(EXIT_FAILURE, parse_tree);
}

void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	printf("minishell: command failed ->" RED "%s" RESET,
		root->content->simple_cmd.cmd_name);
	free(cmd_full_path);
	free(cmd_simple_name);
	ft_splitclear(args);
	exit_command_subshell(EXIT_FAILURE, parse_tree);
}
	// // * in
	// if (root->content->in_redir.file_name)
	// {
	// 	if (in != STDIN_FILENO)
	// 		close(in);
	// 	in = open(root->content->in_redir.file_name, O_RDONLY);
	// }
	// if (in != STDIN_FILENO)
	// {
	// 	dup2(in, STDIN_FILENO);
	// 	close(in);
	// }
	// // * out
	// if (root->content->out_redir.file_name)
	// {
	// 	if (out != STDOUT_FILENO)
	// 		close(out);
	// 	if (root->content->out_redir.append_mode == e_true)
	// 		out = open(root->content->out_redir.file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
	// 	else
	// 		out = open(root->content->out_redir.file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	// }
	// if (out != STDOUT_FILENO)
	// {
	// 	dup2(out, STDOUT_FILENO);
	// 	close(out);
	// }
	// // * redir END

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












