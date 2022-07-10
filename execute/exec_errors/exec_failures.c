/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_failures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:56:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/04 11:46:08 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_errors.h"

void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	printf("minishell: command not found ->" RED " %s\n" RESET,
		parse_tree->content->simple_cmd.cmd_name);
	if (cmd_full_path)
		;
	ft_free(cmd_full_path);
	ft_free(cmd_simple_name);
	ft_splitclear(cmd_args);
	// free(cmd_args);
	exit(EXIT_SUCCESS);
	// exit_command_subshell(EXIT_FAILURE, parse_tree);
}

void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	printf("minishell: command failed ->" RED " %s\n" RESET,
		parse_tree->content->simple_cmd.cmd_name);
	if (cmd_full_path)
		;
	ft_free(cmd_full_path);
	ft_free(cmd_simple_name);
	ft_splitclear(cmd_args);
	// free(cmd_args);
	exit(EXIT_FAILURE);
	// exit_command_subshell(EXIT_FAILURE, parse_tree);
}
