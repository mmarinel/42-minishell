/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:20:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 10:21:12 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FAILURES_H
# define EXEC_FAILURES_H

# include "../executor.h"

void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char *cmd_args);
void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char *cmd_args);

#endif