/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:01:29 by mmarinel          #+#    #+#             */
/*   Updated: 2022/07/03 11:58:54 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../executor.h"

void	execute_env_statement(t_tree_node *root, int in, int out);
void	execute_exit(t_simple_command_node cmd, char *simple_cmd_name);
void	execute_pwd(t_simple_command_node cmd, char *simple_cmd_name);

#endif