/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 11:30:34 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 18:47:10 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	execute_env_arguments_handling(char *arguments,
					t_env_decl_node *bindings_node,
					t_simple_command_node *cmd_node);
static void		execute_env_happy_path(char *argument,
					t_simple_command_node cmd_node,
					t_env_decl_node bindings_node);
static void		execute_env_print_error(t_simple_command_node cmd_node);
//* end of static declarations

void	execute_env(char *arguments)
{
	t_env_decl_node			bindings_node;
	t_simple_command_node	cmd_node;

	cmd_node.cmd_name = NULL;
	cmd_node.cmd_args = NULL;
	bindings_node.bindings = NULL;
	if (ERROR == execute_env_arguments_handling(arguments,
			&bindings_node, &cmd_node))
		execute_env_print_error(cmd_node);
	else
		execute_env_happy_path(arguments, cmd_node, bindings_node);
	free_env(bindings_node.bindings);
	free(cmd_node.cmd_args);
	free(cmd_node.cmd_name);
}

static t_status	execute_env_arguments_handling(char *arguments,
			t_env_decl_node *bindings_node, t_simple_command_node *cmd_node)
{
	t_status	outcome;
	char		**split;

	if (arguments)
	{
		split = ft_split(arguments, ' ');
		outcome = env_set_bindings_and_utility(split,
				cmd_node, bindings_node);
		ft_splitclear(split);
	}
	else
		outcome = OK;
	return (outcome);
}

static void	execute_env_print_error(t_simple_command_node cmd_node)
{
	if (0 == ft_strcmp(cmd_node.cmd_name, "export")
		|| 0 == ft_strcmp(cmd_node.cmd_name, "unset")
		|| 0 == ft_strcmp(cmd_node.cmd_name, "exit"))
		put_error(ENV_CMD_NOT_FOUND_ERR, 127, cmd_node.cmd_name);
	else
		put_error(ENV_OPT_ERR, EXIT_FAILURE, NULL);
}

static void	execute_env_happy_path(char *arguments,
				t_simple_command_node cmd_node,
				t_env_decl_node bindings_node)
{
	if (NULL == arguments)
		print_env();
	else
	{
		if (cmd_node.cmd_name)
			execute_utility(bindings_node, cmd_node);
		else
			execute_empty_utility(bindings_node);
	}
}
