/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:51:44 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/12 18:02:55 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_statements.h"

static void	execute_external_failure_path(void);
static void	execute_external_happy_path(t_tree_node *root);
static void	launch_external_command(t_tree_node *root,
				char *cmd_full_path, char *cmd_simple_name,
				char **args_split);
//* end of static declarations

void	execute_external_simple_cmd(t_tree_node *root, int in, int out)
{
	if (ERROR == external_handle_redirs(root->content->in_redir,
			in, STDIN_FILENO, e_true)
		|| ERROR == external_handle_redirs(root->content->out_redir,
			out, STDOUT_FILENO, e_false))
	{
		execute_external_failure_path();
	}
	else
	{
		execute_external_happy_path(root);
	}
}

static void	execute_external_failure_path(void)
{
	perror("minishell");
	exit(1);
}

static void	execute_external_happy_path(t_tree_node *root)
{
	char		*cmd_simple_name;
	char		*cmd_full_path;
	char		**args_split;

	cmd_expand(&root->content->simple_cmd);
	if (NULL == root->content->simple_cmd.cmd_name)
		exit(EXIT_SUCCESS);
	else
	{
		cmd_simple_name = ft_get_cmd_name(root->content->simple_cmd.cmd_name);
		cmd_full_path = ft_get_pathname(root->content->simple_cmd.cmd_name);
		args_split = ft_split(
				ft_strjoin(
					ft_strjoin(cmd_simple_name, " ", e_false, e_false),
					ft_strdup(root->content->simple_cmd.cmd_args),
					e_true, e_true
					),
				' ');
		launch_external_command(root, cmd_full_path, cmd_simple_name,
			args_split);
	}
}

static void	launch_external_command(t_tree_node *root,
				char *cmd_full_path, char *cmd_simple_name,
				char **args_split)
{
	t_bindings	*env;

	env = env_handler(ENV_RETURN, NULL);
	if (!cmd_full_path)
		command_not_found_failure(root,
			cmd_full_path, cmd_simple_name, args_split);
	if (-1 == execve(cmd_full_path, args_split, bindings_list_to_array(env)))
		command_execution_failure(root,
			cmd_full_path, cmd_simple_name, args_split);
}
