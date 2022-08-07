/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:34:00 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 19:28:13 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_tree_node	*create_cmd_tree_node(t_simple_command_node cmd_node);
//* end of static decalrations

/**
 * @brief this function executes when the env utility is called with
 * an optional list of bindings followed by the name of a utility
 * to be run.
 * 
 * @param bindings_node 
 * @param cmd_node 
 */
void		execute_utility(t_env_decl_node bindings_node,
					t_simple_command_node cmd_node)
{
	t_branch	utility;
	t_tree_node	*cmd_tree_node;

	utility.pid = fork();
	if (0 == utility.pid)
	{
		bindings_node.set = e_true;
		cmd_tree_node = create_cmd_tree_node(cmd_node);
		execute_env_statement(bindings_node);
		execute_rec(cmd_tree_node, STDIN_FILENO, STDOUT_FILENO);
		free_tree(&cmd_tree_node);
		exit(g_env.last_executed_cmd_exit_status);
	}
	else
	{
		waitpid(utility.pid, &(utility.exit_status), 0);
		g_env.last_executed_cmd_exit_status = WEXITSTATUS(utility.exit_status);
	}
}

/**
 * @brief this functions executes the env utility when
 * it is given only a list of bindings.
 * The environment is printed along with the given bindings
 * which will not be added to the current environment.
 * 
 * @param bindings_node the argument given to the env utility
 * @param cmd_node 
 */
void		execute_empty_utility(t_env_decl_node bindings_node)
{
	t_bindings	*bindings;

	bindings = bindings_node.bindings;
	execute_env(NULL);
	while (bindings)
	{
		if (bindings->var_val)
		{
			ft_printf("%s=%s\n", bindings->var_name, bindings->var_val);
		}
		bindings = bindings->next;
	}
}

/**
 * @brief this functions prints the current environment to stdout.
 * 
 */
void	print_env(void)
{
	t_bindings	*env;

	env = (t_bindings *) env_handler(EXPORT_RETURN, NULL);
	while (env)
	{
		if (env->var_val)
		{
			ft_printf("%s=%s\n", env->var_name, env->var_val);
		}
		env = env->next;
	}
	g_env.last_executed_cmd_exit_status = EXIT_SUCCESS;
}

static t_tree_node	*create_cmd_tree_node(t_simple_command_node cmd_node)
{
	t_tree_node	*cmd_tree_node;

	cmd_tree_node = (t_tree_node *) malloc(sizeof(t_tree_node));
	cmd_tree_node->left = NULL;
	cmd_tree_node->right = NULL;
	cmd_tree_node->to_string = NULL;
	cmd_tree_node->content = (t_node_content *) malloc(sizeof(t_node_content));
	cmd_tree_node->content->content_type = SIMPL_CMD;
	cmd_tree_node->content->simple_cmd.cmd_name = ft_strdup(cmd_node.cmd_name);
	cmd_tree_node->content->simple_cmd.cmd_args = ft_strdup(cmd_node.cmd_args);
	cmd_tree_node->content->in_redir.file_name = NULL;
	cmd_tree_node->content->out_redir.file_name = NULL;
	return (cmd_tree_node);
}
