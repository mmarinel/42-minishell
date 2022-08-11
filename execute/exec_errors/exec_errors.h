/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:20:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/08/11 18:49:53 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_ERRORS_H
# define EXEC_ERRORS_H

# include "../executor.h"

//* Failures //
void	command_not_found_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args);
void	command_execution_failure(t_tree_node *parse_tree,
			char *cmd_full_path, char *cmd_simple_name, char **cmd_args);

#endif