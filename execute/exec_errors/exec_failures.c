/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_failures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 09:56:21 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/20 11:16:57 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_errors.h"

void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	put_error(CMD_NOT_FOUND_ERROR, 127,
		parse_tree->content->simple_cmd.cmd_name);
	ft_free(cmd_full_path);
	ft_free(cmd_simple_name);
	ft_splitclear(cmd_args);
	// free(cmd_args);
	exit(127);
	// exit_command_subshell(EXIT_FAILURE, parse_tree);
}

void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args)
{
	put_error(CMD_FAILED_ERROR, EXIT_FAILURE,
		parse_tree->content->simple_cmd.cmd_name);
	ft_free(cmd_full_path);
	ft_free(cmd_simple_name);
	ft_splitclear(cmd_args);
	// free(cmd_args);
	exit(EXIT_FAILURE);
	// exit_command_subshell(EXIT_FAILURE, parse_tree);
}
