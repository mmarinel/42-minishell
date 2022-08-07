/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 11:30:34 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/07 19:32:40 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_status	env_arguments_handling(char *arguments,
			t_env_decl_node *bindings_node, t_simple_command_node *cmd_node);
//* end of static declarations

void	execute_env(char *arguments)
{
	t_env_decl_node			bindings_node;
	t_simple_command_node	cmd_node;

	cmd_node.cmd_name = NULL;
	cmd_node.cmd_args = NULL;
	bindings_node.bindings = NULL;
	if (ERROR == env_arguments_handling(arguments,
					&bindings_node, &cmd_node))
		put_error(ENV_OPT_ERR, EXIT_FAILURE, NULL);
	else
	{
		if (NULL == arguments)
			print_env();
		else
		{
			if (cmd_node.cmd_name)
				execute_utility(bindings_node, cmd_node);
			else
				execute_empty_utility(bindings_node);
			free_env(bindings_node.bindings);
			free(cmd_node.cmd_args);
			free(cmd_node.cmd_name);
		}
	}
}

static t_status	env_arguments_handling(char *arguments,
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
