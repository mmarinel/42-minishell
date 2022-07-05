/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:15:30 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/05 15:11:19 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

static void	executor_handle_redirs(t_redirection redir, int cur_in_out,
			int	std_in_out, t_bool redirect_input);

// * end of declarations //


void	execute_simple_cmd(t_tree_node *root, int in, int out)
{
	char	*cmd_simple_name;
	char	*cmd_full_path;
	char	**args;

	// printf(YELLOW "execute_simple_cmd\n" RESET);
	args = NULL;
	if (in && out)
		;
	executor_handle_redirs(root->content->in_redir,
		in, STDIN_FILENO, e_true);
	executor_handle_redirs(root->content->out_redir,
		out, STDOUT_FILENO, e_false);
	cmd_simple_name = ft_get_cmd_name(root->content->simple_cmd.cmd_name);
	cmd_full_path = ft_get_pathname(root->content->simple_cmd.cmd_name);
	// printf("simple name: %s\tlen: %zu\n", cmd_simple_name, ft_strlen(cmd_simple_name));
	// printf("full name: %s\tlen: %zu\n", cmd_full_path, ft_strlen(cmd_full_path));
	// printf("full name: %s\n", root->content->simple_cmd.cmd_args);
	args = ft_split(
			ft_strjoin(
				ft_strjoin(cmd_simple_name, " ", e_false, e_false),
				root->content->simple_cmd.cmd_args, e_true, e_false),
			' ');
	if (!cmd_full_path)
		command_not_found_failure(root, cmd_full_path, cmd_simple_name, args);
	// printf("cmd_full_path is: %s\n", cmd_full_path);
	// char	**envp;
	// envp = bindings_list_to_array(g_env.env);
	// while (*envp)
	// {
	// 	printf("%s\n", *envp);
	// 	envp++;
	// }
	// exit(0);
	// int j = 0;
	// while (args[j])
	// {
	// 	printf("arg: %s\n", args[j]);
	// 	j++;
	// }
	// exit(0);
	if (-1 == execve(cmd_full_path, args, bindings_list_to_array(env_handler(ENV_RETURN, NULL))))//bindings_list_to_array(g_env.env)))
		command_execution_failure(root, cmd_full_path, cmd_simple_name, args);
}

// t_bool	execute_builtin(t_simple_command_node cmd, int in, int out)
// {
// 	char	*simple_name;

// 	simple_name = ft_get_cmd_name(cmd.cmd_name);
// 	if (0 == ft_strcmp(simple_name, "echo"))
// 		execute_echo(cmd);
// 	if (0 == ft_strcmp(simple_name, "cd"))
// 		execute_cd(cmd);
// 	if (0 == ft_strcmp(simple_name, "pwd"))
// 		execute_pwd(cmd);
// 	if (0 == ft_strcmp(simple_name, "export"))
// 		execute_export(cmd);
// 	if (0 == ft_strcmp(simple_name, "unset"))
// 		execute_unset(cmd);
// 	if (0 == ft_strcmp(simple_name, "env"))
// 		execute_env(cmd);
// 	if (0 == ft_strcmp(simple_name, "exit"))
// 		execute_exit(cmd, simple_name);
// 	free(simple_name);
// 	if (g_env.last_executed_cmd_exit_status == EXIT_FAILURE)
// 		exit(EXIT_FAILURE); // * mettere una exit_shell custom in ogni modulo ! (per freeare tutto il necessario)
// 	else
// 		exit(EXIT_SUCCESS); // * mettere una exit_shell custom in ogni modulo ! (per freeare tutto il necessario)
// }

void	execute_redir_only_statement(t_tree_node *root, int in, int out)
{
	int	out_fd;

	printf(YELLOW "execute_redir_only_statement\n" RESET);
	out_fd = 0;
	if (root->content->out_redir.file_name)
	{
		printf("file name is: %s\n", root->content->out_redir.file_name);
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
		;
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
