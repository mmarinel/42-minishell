/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_failures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:56:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/14 19:17:58 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_errors.h"

void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	put_error("minishell: command not found ->",
		parse_tree->content->simple_cmd.cmd_name,
		NULL, e_false);
	ft_free(cmd_full_path);
	ft_free(cmd_simple_name);
	ft_splitclear(cmd_args);
	// free(cmd_args);
	exit(EXIT_FAILURE);
	// exit_command_subshell(EXIT_FAILURE, parse_tree);
}

void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	put_error("minishell: command failed ->",
		parse_tree->content->simple_cmd.cmd_name,
		NULL, e_false);
	ft_free(cmd_full_path);
	ft_free(cmd_simple_name);
	ft_splitclear(cmd_args);
	// free(cmd_args);
	exit(EXIT_FAILURE);
	// exit_command_subshell(EXIT_FAILURE, parse_tree);
}
