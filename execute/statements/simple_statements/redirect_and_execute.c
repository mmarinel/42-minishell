/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:15:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 20:16:23 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

static void	executor_handle_redirs(t_redirection redir, int cur_in_out,
			int	std_in_out, t_bool redirect_input);

static void	execute_cmd_builtin(t_simple_command_node simple_cmd);

// * end of declarations //


void	execute_simple_cmd(t_tree_node *root, int in, int out)
{
	char		*cmd_simple_name;
	char		*cmd_full_path;
	char		**args_split;
	t_bindings	*env;

	env = env_handler(ENV_RETURN, NULL);
	executor_handle_redirs(root->content->in_redir,
		in, STDIN_FILENO, e_true);
	executor_handle_redirs(root->content->out_redir,
		out, STDOUT_FILENO, e_false);
	cmd_simple_name = ft_get_cmd_name(root->content->simple_cmd.cmd_name);
	cmd_full_path = ft_get_pathname(root->content->simple_cmd.cmd_name);
	args_split = ft_split(
			ft_strjoin(
				ft_strjoin(cmd_simple_name, " ", e_false, e_false),
				expand(ft_strdup(root->content->simple_cmd.cmd_args)),
				e_true, e_true
			),
		' ');
	if (!cmd_full_path)
		command_not_found_failure(root,
			cmd_full_path, cmd_simple_name, args_split);
	if (-1 == execve(cmd_full_path, args_split, bindings_list_to_array(env)))
		command_execution_failure(root,
			cmd_full_path, cmd_simple_name, args_split);
}

void	execute_builtin(t_tree_node *root, int in, int out)
{
	executor_handle_redirs(root->content->in_redir,
		in, STDIN_FILENO, e_true);
	executor_handle_redirs(root->content->out_redir,
		out, STDOUT_FILENO, e_false);
	if (root->content->content_type == ENV_STATEMENT)
	{
		// if (root->content->env_decl.set)
			execute_env_statement(root->content->env_decl);
		// else
		// 	execute_unset(root->content->env_decl);
	}
	else if (root->content->content_type == REDIR)
	{
		execute_redir_only_statement(root, in, out);
	}
	else
	{
		execute_cmd_builtin(root->content->simple_cmd);
	}
}

void	execute_redir_only_statement(t_tree_node *root, int in, int out)
{
	int	out_fd;

	// printf(YELLOW "execute_redir_only_statement\n" RESET);
	out_fd = 0;
	if (root->content->out_redir.file_name)
	{
		// printf("file name is: %s\n", root->content->out_redir.file_name);
		if (root->content->out_redir.append_mode == e_true)
			out_fd = open(root->content->out_redir.file_name,
						O_CREAT | O_APPEND | O_WRONLY, 0777);
		else
			out_fd = open(root->content->out_redir.file_name,
						O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (out_fd == -1)
		{
			perror("minishell at execute_redir_only_statement: ");
			g_env.last_executed_cmd_exit_status = EXIT_FAILURE;
		}
		else
			close(out_fd);
	}
	// printf(YELLOW "at the end of execute_redir_only\n" RESET);
	exit(g_env.last_executed_cmd_exit_status);
	if (in || out)
	{}
}

static void	executor_handle_redirs(t_redirection redir, int cur_in_out,
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
					cur_in_out = ft_open_file(redir.file_name,
								O_CREAT | O_APPEND | O_WRONLY, 0777);
				else
					cur_in_out = ft_open_file(redir.file_name,
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

static void	execute_cmd_builtin(t_simple_command_node simple_cmd)
{
	char	*simple_name;

	simple_cmd.cmd_args = expand(simple_cmd.cmd_args);
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
		execute_env();
	free(simple_name);
	// if (g_env.last_executed_cmd_exit_status == EXIT_FAILURE)
	// 	exit(EXIT_FAILURE); // * mettere una exit_shell custom in ogni modulo ! (per freeare tutto il necessario)
	// else
	// 	exit(EXIT_SUCCESS); // * mettere una exit_shell custom in ogni modulo ! (per freeare tutto il necessario)
}
