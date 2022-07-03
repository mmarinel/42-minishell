/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_failures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:56:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 09:57:09 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	printf("minishell: command not found ->" RED "%s" RESET,
		parse_tree->content->simple_cmd.cmd_name);
	free(cmd_full_path);
	free(cmd_simple_name);
	ft_splitclear(cmd_args);
	exit_command_subshell(EXIT_FAILURE, parse_tree);
}

void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	printf("minishell: command failed ->" RED "%s" RESET,
		parse_tree->content->simple_cmd.cmd_name);
	free(cmd_full_path);
	free(cmd_simple_name);
	ft_splitclear(cmd_args);
	exit_command_subshell(EXIT_FAILURE, parse_tree);
}
